// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Character/SurvivorCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "JMS/DataAsset/DA_SurvivorInput.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/AssetManager.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "JMS/Component/SurvivorInteractableComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GE/GE_SurvivorResetDyingHP.h"
#include "JMS/GAS/GE/GE_SurvivorResetHealProgress.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"
#include "Shared/Controller/DBDPlayerController.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDGameMode.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/DBDHUD.h"

ASurvivorCharacter::ASurvivorCharacter()
{
	// GAS
	SurvivorAbilitySystemComponent = CreateDefaultSubobject<USurvivorAbilitySystemComponent>(
		TEXT("SurvivorAbilitySystemComponent"));
	SurvivorAttributeSet = CreateDefaultSubobject<USurvivorAttributeSet>(TEXT("SurvivorAttributeSet"));

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);


	bUseControllerRotationYaw = false;

	// SkillCheckComponent
	SkillCheckComponent = CreateDefaultSubobject<USkillCheckComponent>(TEXT("SkillCheckComponent"));

	// InteractorComponent
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	InteractorComponent->SetupAttachment(GetRootComponent());

	// InteractableComponent
	SurvivorInteractableComponent = CreateDefaultSubobject<USurvivorInteractableComponent>(
		TEXT("SurvivorInteractableComponent"));
	SurvivorInteractableComponent->SetupAttachment(GetRootComponent());


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.0f, 0.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	BindGASChangeDelegate();
}

UAbilitySystemComponent* ASurvivorCharacter::GetAbilitySystemComponent() const
{
	return SurvivorAbilitySystemComponent;
}

void ASurvivorCharacter::RegisterHook(AObj_Hook* Hook)
{
	if (Hook)
	{
		CurrentHook = Hook;
	}
}

AObj_Hook* ASurvivorCharacter::GetCurrentHook() const
{
	return CurrentHook;
}

void ASurvivorCharacter::OnRep_EquippedItem(ASurvivorItem* OldItem)
{
	if (OldItem && OldItem != EquippedItem)
	{
		OldItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	if (EquippedItem)
	{
		EquippedItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		                                ItemSocketName);
	}
	UpdateCurrentItemUI();
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!IsLocallyControlled())
	{
		return;
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this,
		                                   &ASurvivorCharacter::LookAction);
		EnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this,
		                                   &ASurvivorCharacter::MoveAction);

		for (const TPair<ESurvivorAbilityInputID, UInputAction*>& InputActionPair : InputData->
		     GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this,
			                                   &ASurvivorCharacter::AbilityInput, InputActionPair.Key);
		}
		if (SkillCheckComponent)
		{
			SkillCheckComponent->SetupInputActionBinding(EnhancedInputComponent);
		}
	}
}

void ASurvivorCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	APlayerController* PC = GetController<APlayerController>();
	if (PC)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(InputData->InputMappingContext,
			                                  InputData->InputMappingContextPriority);
		}
	}
}

void ASurvivorCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// ADBDPlayerState* PS = Cast<ADBDPlayerState>(GetPlayerState());
	// if (EquippedItem)
	// {
	// 	Debug::Print(TEXT("JMS11 : Survivor Item : ") + EquippedItem->GetName(), 11);
	// }
	// else
	// {
	// 	Debug::Print(TEXT("JMS11 : Survivor Item : None"), 11);
	// }
	// if (PS)
	// {
	// 	if (PS->SurvivorLoadout.ItemInfo.Item.IsValid())
	// 	{
	// 		Debug::Print(TEXT("JMS12 : Survivor Item Info: ") + PS->SurvivorLoadout.ItemInfo.Item.ToString(), 12);
	// 	}
	// }
}

void ASurvivorCharacter::HealProgressChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	bool bFound1,bFound2 = false;
	float CurrentHealProgress = SurvivorAbilitySystemComponent->GetGameplayAttributeValue(
		USurvivorAttributeSet::GetHealProgressAttribute(), bFound1);
	float MaxHealProgress = SurvivorAbilitySystemComponent->GetGameplayAttributeValue(
		USurvivorAttributeSet::GetMaxHealProgressAttribute(), bFound2);
	if (bFound1&&bFound2)
	{
		if (CurrentHealProgress >= MaxHealProgress)
		{
			SetSurvivorNormal();
			SurvivorInteractableComponent->OnComplete.Broadcast();
		}
	}
}

void ASurvivorCharacter::DyingHPChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	bool bFound1,bFound2 = false;
	float CurrentDyingHP = SurvivorAbilitySystemComponent->GetGameplayAttributeValue(
		USurvivorAttributeSet::GetDyingHPAttribute(), bFound1);
	float MaxDyingHP = SurvivorAbilitySystemComponent->GetGameplayAttributeValue(
		USurvivorAttributeSet::GetMaxDyingHPAttribute(), bFound2);
	if (bFound1&&bFound2)
	{
		if (CurrentDyingHP >= MaxDyingHP)
		{
			SetSurvivorInjured();
			SurvivorInteractableComponent->OnComplete.Broadcast();
		}
	}
}

void ASurvivorCharacter::BindGASChangeDelegate()
{
	if (SurvivorAbilitySystemComponent)
	{
		SurvivorAbilitySystemComponent->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Dead).AddUObject(
			this, &ASurvivorCharacter::DeathTagUpdate);
		SurvivorAbilitySystemComponent->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Escaped).AddUObject(
			this, &ASurvivorCharacter::EscapeTagUpdate);
	}
	SurvivorAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetHealProgressAttribute()).AddUObject(
		this, &ASurvivorCharacter::HealProgressChanged);
	SurvivorAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetDyingHPAttribute()).AddUObject(
		this, &ASurvivorCharacter::DyingHPChanged);
}

void ASurvivorCharacter::DeathTagUpdate(const FGameplayTag Tag, int32 NewCount)
{
	// ADBDPlayerController* PC = GetController<ADBDPlayerController>();
	// if (PC)
	// {
	// 	PC->EnterSpectatorCam();
	// }
	SetCollisionAndGravityEnabled(false);
	SetActorHiddenInGame(true);
	if (EquippedItem)
	{
		EquippedItem->SetActorHiddenInGame(true);
	}
	if (HasAuthority())
	{
		ADBDGameMode* DBDGM = Cast<ADBDGameMode>(UGameplayStatics::GetGameMode(this));
		if (DBDGM)
		{
			DBDGM->CheckGameCondition();
		}
	}
}

void ASurvivorCharacter::EscapeTagUpdate(const FGameplayTag Tag, int32 NewCount)
{
	// ADBDPlayerController* PC = GetController<ADBDPlayerController>();
	// if (PC)
	// {
	// 	PC->EnterSpectatorCam();
	// }
	SetCollisionAndGravityEnabled(false);
	SetActorHiddenInGame(true);
	if (EquippedItem)
	{
		EquippedItem->SetActorHiddenInGame(true);
	}
	if (HasAuthority())
	{
		ADBDGameMode* DBDGM = Cast<ADBDGameMode>(UGameplayStatics::GetGameMode(this));
		if (DBDGM)
		{
			DBDGM->CheckGameCondition();
		}
	}
}

ADBDPlayerState* ASurvivorCharacter::GetDBDPlayerState() const
{
	return Cast<ADBDPlayerState>(GetPlayerState());
}

void ASurvivorCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ASurvivorCharacter, EquippedItem, COND_None, REPNOTIFY_Always);
}


void ASurvivorCharacter::AbilityInput(const FInputActionValue& InputActionValue, ESurvivorAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		SurvivorAbilitySystemComponent->AbilityLocalInputPressed((int32)InputID);
	}
	else
	{
		SurvivorAbilitySystemComponent->AbilityLocalInputReleased((int32)InputID);
	}
}


void ASurvivorCharacter::LookAction(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ASurvivorCharacter::MoveAction(const FInputActionValue& InputActionValue)
{
	if (SurvivorAbilitySystemComponent->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_MoveDisabled))
	{
		return;
	}
	FVector2D InputValue = InputActionValue.Get<FVector2D>();

	AddMovementInput(GetMoveForwardDirection() * InputValue.Y + GetLookRightDirection() * InputValue.X);
}

FVector ASurvivorCharacter::GetLookRightDirection() const
{
	return FollowCam->GetRightVector();
}

FVector ASurvivorCharacter::GetLookForwardDirection() const
{
	return FollowCam->GetForwardVector();
}

FVector ASurvivorCharacter::GetMoveForwardDirection() const
{
	return FVector::CrossProduct(GetLookRightDirection(), FVector::UpVector);
}

void ASurvivorCharacter::UpdateCurrentItemUI()
{
	EquippedItemChangedDelegate.Broadcast(EquippedItem);
}


void ASurvivorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController)
	{
		ServerSideInit();
	}
}

void ASurvivorCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	ClientSideInit();
}

void ASurvivorCharacter::EquipItem(ASurvivorItem* ItemToEquip)
{
	if (ItemToEquip)
	{
		ItemToEquip->SetOwner(this);
		ItemToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		                               ItemSocketName);
		ItemToEquip->OnEquipItem();
		EquippedItem = ItemToEquip;
	}
	UpdateCurrentItemUI();
}

void ASurvivorCharacter::DropItem()
{
	if (EquippedItem)
	{
		EquippedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedItem->OnDropItem();
		EquippedItem->SetOwner(nullptr);
		FVector Start = GetActorLocation();
		FVector End = Start - FVector(0, 0, 200.0f);

		FHitResult HitResult;
		FCollisionShape Shape = FCollisionShape::MakeSphere(10.0f); // 반지름 10짜리 구체로 검사

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			Start,
			End,
			FQuat::Identity,
			ECC_Visibility,
			Shape,
			Params
		);

		if (bHit)
		{
			FVector DropLocation = HitResult.Location;
			EquippedItem->SetActorLocation(DropLocation);
		}
		else
		{
			EquippedItem->SetActorLocation(Start);
		}
		EquippedItem = nullptr;
	}
	UpdateCurrentItemUI();
}

void ASurvivorCharacter::ExchangeItem(ASurvivorItem* ItemToExchange)
{
	UpdateCurrentItemUI();
}


void ASurvivorCharacter::UseEquippedItem()
{
	if (EquippedItem)
	{
		EquippedItem->OnItemUsed();
	}
}

UInteractableComponent* ASurvivorCharacter::GetInteractableComponent() const
{
	return SurvivorInteractableComponent;
}

UInteractorComponent* ASurvivorCharacter::GetInteractorComponent() const
{
	return InteractorComponent;
}

EPlayerRole ASurvivorCharacter::GetInteractorRole() const
{
	return EPlayerRole::Survivor;
}

USkillCheckComponent* ASurvivorCharacter::GetSkillCheckComponent() const
{
	return SkillCheckComponent;
}

void ASurvivorCharacter::MoveEnabled(bool bEnable)
{
	GetCharacterMovement()->SetMovementMode(bEnable ? MOVE_Walking : MOVE_None);
}

void ASurvivorCharacter::SetCollisionAndGravityEnabled(bool bEnable)
{
	GetCharacterMovement()->SetMovementMode(bEnable ? MOVE_Walking : MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(bEnable
		                                           ? ECollisionEnabled::QueryAndPhysics
		                                           : ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, bEnable ? ECR_Block : ECR_Ignore);
	GetCharacterMovement()->GravityScale = bEnable ? 1.0f : 0.0f;
	GetMesh()->SetEnableGravity(bEnable);
	bIsCollisionAndGravityEnabled = bEnable;
}

bool ASurvivorCharacter::IsCollisionAndGravityEnabled() const
{
	return bIsCollisionAndGravityEnabled;
}

void ASurvivorCharacter::AttackSurvivor()
{
	if (SurvivorAbilitySystemComponent->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Dying))
	{
	}
	else if (SurvivorAbilitySystemComponent->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Injured))
	{
		SetSurvivorDying();
	}
	else
	{
		SetSurvivorInjured();
	}
}

void ASurvivorCharacter::SetSurvivorInjured()
{
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Normal);
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Injured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Dying);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_CaptureEnabled);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Captured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Hooked);
	SurvivorAbilitySystemComponent->BP_ApplyGameplayEffectToSelf(UGE_SurvivorResetHealProgress::StaticClass(), 0,
	                                                             SurvivorAbilitySystemComponent->
	                                                             MakeEffectContext());
}

void ASurvivorCharacter::SetSurvivorDying()
{
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Normal);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Injured);
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Dying);
	AddUniqueTag(DBDGameplayTags::Survivor_Status_CaptureEnabled);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Captured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Hooked);
	SurvivorAbilitySystemComponent->BP_ApplyGameplayEffectToSelf(UGE_SurvivorResetDyingHP::StaticClass(), 0,
															 SurvivorAbilitySystemComponent->
															 MakeEffectContext());
}

void ASurvivorCharacter::SetSurvivorNormal()
{
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Normal);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Injured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Dying);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_CaptureEnabled);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Captured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Hooked);
}

void ASurvivorCharacter::CaptureSurvivor()
{
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Normal);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Injured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Dying);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_CaptureEnabled);
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Captured);
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Hooked);
}

void ASurvivorCharacter::HookSurvivor(AObj_Hook* Hook)
{
	AddTag(DBDGameplayTags::Survivor_Status_HookCount);
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Hooked);
	RegisterHook(Hook);
}

void ASurvivorCharacter::ReleaseSurvivor()
{
	SetSurvivorInjured();
	RemoveTagAll(DBDGameplayTags::Survivor_Status_Hooked);
	CurrentHook = nullptr;
}

void ASurvivorCharacter::SetSurvivorEscaped()
{
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Escaped);
}

void ASurvivorCharacter::SetSurvivorDead()
{
	AddUniqueTag(DBDGameplayTags::Survivor_Status_Dead);
}

void ASurvivorCharacter::InitializeEquippedItem(FSurvivorItemInstanceInfo InitialItemInfo)
{
	UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance());
	if (!DBDGI)
	{
		return;
	}

	UDataTable* DT = Cast<UDataTable>(
		UAssetManager::Get().GetStreamableManager().LoadSynchronous(
			DBDGI->DBDDB->SurvivorItemDB.ToSoftObjectPath()));

	ASurvivorItem* SpawnedItem = nullptr;

	if (DT)
	{
		FItemData* ItemData = DT->FindRow<FItemData>(InitialItemInfo.Item, "");
		if (ItemData)
		{
			TSubclassOf<ASurvivorItem> ItemClassFromDB = ItemData->ItemClass;
			if (ItemClassFromDB)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnedItem = GetWorld()->SpawnActor<ASurvivorItem>(ItemClassFromDB, SpawnParams);
			}
		}
	}
	else
	{
		Debug::Print(TEXT("JMS111 : SurvivorItemDB Load Failed"), 111);
	}

	if (!SpawnedItem)
	{
		return;
	}

	DT = Cast<UDataTable>(
		UAssetManager::Get().GetStreamableManager().LoadSynchronous(
			DBDGI->DBDDB->ItemAddonDB.ToSoftObjectPath()));
	if (DT)
	{
		if (InitialItemInfo.Addon1 != NAME_None)
		{
			FItemAddonData* ItemAddonData = DT->FindRow<FItemAddonData>(InitialItemInfo.Addon1, "");
			if (ItemAddonData)
			{
				TSubclassOf<UItemAddonComponent> ItemAddonClassFromDB = ItemAddonData->AddonClass;
				if (ItemAddonClassFromDB)
				{
					UItemAddonComponent* ItemAddon = NewObject<UItemAddonComponent>(SpawnedItem, ItemAddonClassFromDB);
					SpawnedItem->AttachAddon1(ItemAddon);
				}
			}
		}
		if (InitialItemInfo.Addon2 != NAME_None)
		{
			FItemAddonData* ItemAddonData = DT->FindRow<FItemAddonData>(InitialItemInfo.Addon2, "");
			if (ItemAddonData)
			{
				TSubclassOf<UItemAddonComponent> ItemAddonClassFromDB = ItemAddonData->AddonClass;
				if (ItemAddonClassFromDB)
				{
					UItemAddonComponent* ItemAddon = NewObject<UItemAddonComponent>(SpawnedItem, ItemAddonClassFromDB);
					SpawnedItem->AttachAddon2(ItemAddon);
				}
			}
		}
	}
	else
	{
		Debug::Print(TEXT("JMS112 : SurvivorItemAddonDB Load Failed"), 111);
	}

	EquipItem(SpawnedItem);
}

void ASurvivorCharacter::ServerSideInit()
{
	SurvivorAbilitySystemComponent->InitAbilityActorInfo(this, this);
	SurvivorAbilitySystemComponent->ServerSideInit();
	ADBDPlayerState* PS = Cast<ADBDPlayerState>(GetPlayerState());
	if (PS)
	{
		AuthInitPerks();
	}
	if (!IsRunningDedicatedServer())
	{
		UDBDAnimInstance* DBDAnimInstance = Cast<UDBDAnimInstance>(GetMesh()->GetAnimInstance());
		if (DBDAnimInstance)
		{
			DBDAnimInstance->InitializeWithAbilitySystem(SurvivorAbilitySystemComponent);
		}
	}
	ADBDPlayerState* DBDPlayerState = GetDBDPlayerState();
	if (!DBDPlayerState)
	{
		return;
	}
	FSurvivorItemInstanceInfo InitialItemInfo = DBDPlayerState->SurvivorLoadout.ItemInfo;
	if (InitialItemInfo.Item != NAME_None)
	{
		InitializeEquippedItem(InitialItemInfo);
	}
}

void ASurvivorCharacter::ClientSideInit()
{
	SurvivorAbilitySystemComponent->InitAbilityActorInfo(this, this);
	UDBDAnimInstance* DBDAnimInstance = Cast<UDBDAnimInstance>(GetMesh()->GetAnimInstance());
	if (DBDAnimInstance)
	{
		DBDAnimInstance->InitializeWithAbilitySystem(SurvivorAbilitySystemComponent);
	}

	TempPrototypeWidget = CreateWidget<UDBDHUD>(GetLocalViewingPlayerController(), TempPrototypeWidgetClass);
	if (TempPrototypeWidget)
	{
		TempPrototypeWidget->AddToViewport();
	}
	UpdateCurrentItemUI();
}

bool ASurvivorCharacter::IsLocallyControlledByPlayer() const
{
	// 로컬제어 & 플레이어 컨트롤러인지 판단
	return GetController() && GetController()->IsLocalPlayerController();
}

void ASurvivorCharacter::AddUniqueTag(FGameplayTag Tag)
{
	ServerAddUniqueTag(Tag);
}

void ASurvivorCharacter::AddTag(FGameplayTag Tag)
{
	ServerAddTag(Tag);
}

void ASurvivorCharacter::ServerAddTag_Implementation(const FGameplayTag& Tag)
{
	SurvivorAbilitySystemComponent->AddLooseGameplayTag(Tag);
	SurvivorAbilitySystemComponent->AddReplicatedLooseGameplayTag(Tag);
}

void ASurvivorCharacter::RemoveTag(FGameplayTag Tag)
{
	ServerRemoveTag(Tag);
}

void ASurvivorCharacter::RemoveTagAll(FGameplayTag Tag)
{
	ServerRemoveTagAll(Tag);
}

void ASurvivorCharacter::ServerRemoveTagAll_Implementation(const FGameplayTag& Tag)
{
	SurvivorAbilitySystemComponent->RemoveLooseGameplayTags(FGameplayTagContainer(Tag),
	                                                        SurvivorAbilitySystemComponent->GetTagCount(Tag));
	SurvivorAbilitySystemComponent->RemoveReplicatedLooseGameplayTags(FGameplayTagContainer(Tag));
}

void ASurvivorCharacter::PrintHasTag(FGameplayTag Tag)
{
	ServerPrintHasTag(Tag);
}

void ASurvivorCharacter::SendGameplayTagEvent(FGameplayTag Tag)
{
	ServerSendGameplayTagEvent(Tag);
}

void ASurvivorCharacter::ServerSendGameplayTagEvent_Implementation(const FGameplayTag& Tag)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag, FGameplayEventData());
}

void ASurvivorCharacter::ServerPrintHasTag_Implementation(const FGameplayTag& Tag)
{
	if (SurvivorAbilitySystemComponent->HasMatchingGameplayTag(Tag))
	{
		UE_LOG(LogTemp, Warning, TEXT("JMS : Tag exist"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("JMS : Tag does not exist"))
	}
}

void ASurvivorCharacter::ServerRemoveTag_Implementation(const FGameplayTag& Tag)
{
	SurvivorAbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	SurvivorAbilitySystemComponent->RemoveReplicatedLooseGameplayTag(Tag);
}

void ASurvivorCharacter::ServerAddUniqueTag_Implementation(const FGameplayTag& Tag)
{
	if (!SurvivorAbilitySystemComponent->HasMatchingGameplayTag(Tag))
	{
		SurvivorAbilitySystemComponent->AddLooseGameplayTag(Tag);
		SurvivorAbilitySystemComponent->AddReplicatedLooseGameplayTag(Tag);
	}
}
