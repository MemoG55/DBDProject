// Fill out your copyright notice in the Description page of Project Settings.

#include "KMJ/Character/KillerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/AnimInstances/KillerAnimInstance.h"
#include "KMJ/Component/KillerInteractableComponent.h"
#include "KMJ/DataAsset/DA_KillerInput.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Component/InteractorComponent.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Slate/SGameLayerManager.h"

AKillerCharacter::AKillerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritRoll = true;
	CameraBoom->bInheritYaw = false;

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	KillerAbilitySystemComponent = CreateDefaultSubobject<UKillerAbilitySystemComponent>(TEXT("KillerAbilitySystemComponent"));
	KillerAttributeSet = CreateDefaultSubobject<UKillerAttributeSet>(TEXT("KillerAttributeSet"));

	// InteractorComponent
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	InteractorComponent->SetupAttachment(GetRootComponent());

	// InteractableComponent
	KillerInteractableComponent = CreateDefaultSubobject<UKillerInteractableComponent>(
		TEXT("KillerInteractableComponent"));
	KillerInteractableComponent->SetupAttachment(GetRootComponent());
}

UAbilitySystemComponent* AKillerCharacter::GetAbilitySystemComponent() const
{
	return KillerAbilitySystemComponent;
}

UInteractableComponent* AKillerCharacter::GetInteractableComponent() const
{
	return KillerInteractableComponent;
}

UInteractorComponent* AKillerCharacter::GetInteractorComponent() const
{
	return InteractorComponent;
}

EPlayerRole AKillerCharacter::GetInteractorRole() const
{
	return EPlayerRole::Killer;
}

void AKillerCharacter::ServerSideInit()
{
	KillerAbilitySystemComponent->InitAbilityActorInfo(this, this);
	KillerAbilitySystemComponent->ApplyInitializeEffects();
	KillerAbilitySystemComponent->OperatingInitializedAbilities();
	ADBDPlayerState* PS = Cast<ADBDPlayerState>(GetPlayerState());
	if (PS)
	{
		AuthInitPerks();
	}
	if (!IsRunningDedicatedServer())
	{
		UKillerAnimInstance* KillerAnimInstance = Cast<UKillerAnimInstance>(GetMesh()->GetAnimInstance());
		if (KillerAnimInstance)
		{
			//UE_LOG(LogTemp, Error, TEXT("KillerCharacter::ServerSideInit: KillerAnimInstance Is %s"), *KillerAnimInstance->GetName());
			KillerAnimInstance->InitializeWithAbilitySystem(KillerAbilitySystemComponent);
		}
		else
		{
		    //UE_LOG(LogTemp, Error, TEXT("KillerCharacter::ServerSideInit: KillerAnimInstance Is Null"));
		}
	}
}

void AKillerCharacter::ClientSideInit()
{
	KillerAbilitySystemComponent->InitAbilityActorInfo(this, this);
	UKillerAnimInstance* KillerAnimInstance = Cast<UKillerAnimInstance>(GetMesh()->GetAnimInstance());
	if (KillerAnimInstance)
	{
		//UE_LOG(LogTemp, Error, TEXT("KillerCharacter::ClientSideInit: KillerAnimInstance Is %s"), *KillerAnimInstance->GetName());
		KillerAnimInstance->InitializeWithAbilitySystem(KillerAbilitySystemComponent);
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("KillerCharacter::ClientSideInit: KillerAnimInstance Is Null"));
	}
}

void AKillerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetController())
	{
		if (FPVAnimClass)
		{
			GetMesh()->SetAnimInstanceClass(FPVAnimClass);
			//Debug::Print(FString::Printf(TEXT("KMJ:: %s: FPV: %s"), *GetController()->GetCharacter()->GetName() ,*FPVAnimClass->GetName()), 3);
			//UE_LOG(LogTemp, Warning, TEXT("FPV: %s"), *FPVAnimClass->GetName());
		}
		//else UE_LOG(LogTemp, Warning, TEXT("FPVAnimClass is null!"));
	}
	else
	{
		if (TPVAnimClass)
		{
			GetMesh()->SetAnimInstanceClass(TPVAnimClass);
			//Debug::Print(FString::Printf(TEXT("KMJ:: %s: TPV: %s"), *GetController()->GetCharacter()->GetName(),*TPVAnimClass->GetName()), 3);
			//UE_LOG(LogTemp, Warning, TEXT("TPV: %s"), *TPVAnimClass->GetName());
		}
		//else UE_LOG(LogTemp, Warning, TEXT("TPVAnimClass is null!"));
	}
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AKillerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	}
	else
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	}

	//상태 정의 코드
	bIsGrounded = GetCharacterMovement()->IsMovingOnGround();
	bIsFalling = GetCharacterMovement()->IsFalling();
	//아무런 움직임이 없고, 지상일 때
	bIsIdle = GetCharacterMovement()->Velocity.IsZero() && bIsGrounded;

	//카메라 기준 오른쪽으로 움직이는지, 왼쪽으로 움직이는지
	FVector VelocityDirection = GetCharacterMovement()->Velocity.GetSafeNormal();
	bIsLeftMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCam->GetForwardVector()).Z > 0;
	bIsRightMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCam->GetForwardVector()).Z < 0;

	if ((bIsLeftMoving && bIsRightMoving) || (!bIsLeftMoving && !bIsRightMoving))
	{
		if (FMath::RandBool())
		{
			bIsLeftMoving = true;
			bIsRightMoving = false;
		}
		else
		{
			bIsLeftMoving = false;
			bIsRightMoving = true;
		}
	}
}

void AKillerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController)
	{
		ServerSideInit();
	}
}

void AKillerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//if (IsLocallyControlledByPlayer())
	//{
		ClientSideInit();
	//}
}

bool AKillerCharacter::IsLocallyControlledByPlayer() const
{
	// 로컬제어 & 플레이어 컨트롤러인지 판단
	return GetController() && GetController()->IsLocalPlayerController();
}

void AKillerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this,
										   &AKillerCharacter::LookAction);
		EnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this,
										   &AKillerCharacter::MoveAction);

		for (const TPair<EKillerAbilityInputID, UInputAction*>& InputActionPair : InputData->
			 GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this,
											   &AKillerCharacter::AbilityInput, InputActionPair.Key);
		}
	}
}

void AKillerCharacter::PawnClientRestart()
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

void AKillerCharacter::OnRep_CarriedSurvivorCharacter()
{
}

void AKillerCharacter::Server_SetCarriedSurvivorCharacter_Implementation(ASurvivorCharacter* NewSurvivorCharacter)
{
	// 유효한 생존자 캐릭터인지 확인
	if (IsValid(NewSurvivorCharacter))
	{
		CarriedSurvivorCharacter = NewSurvivorCharacter;

		// 레플리케이션을 트리거하여 클라이언트에 동기화
		OnRep_CarriedSurvivorCharacter();  // 클라이언트 측에서 처리할 내용도 추가 가능

		// 추가적인 서버측 로직 처리 가능 (예: 능력 시스템 등)
		//UE_LOG(LogTemp, Log, TEXT("Carried Survivor Character set to: %s"), *NewSurvivorCharacter->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Invalid Survivor Character passed to server!"));
	}
}

bool AKillerCharacter::Server_SetCarriedSurvivorCharacter_Validate(ASurvivorCharacter* NewSurvivorCharacter)
{
	// 여기서 적절한 검증 로직을 추가합니다. 예를 들어:
	if (IsValid(NewSurvivorCharacter))
	{
		// 생존자가 유효하고 살아있는지 확인
		return true;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Invalid Survivor Character passed to server during validation!"));
		return false; // 클라이언트가 보낸 데이터가 유효하지 않으면 false 반환
	}
}

void AKillerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKillerCharacter, CarriedSurvivorCharacter);
}

void AKillerCharacter::AbilityInput(const FInputActionValue& InputActionValue, EKillerAbilityInputID InputID)
{
	const bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}

void AKillerCharacter::LookAction(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void AKillerCharacter::MoveAction(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();

	AddMovementInput(GetMoveForwardDirection() * InputValue.Y + GetLookRightDirection() * InputValue.X);
}

FVector AKillerCharacter::GetLookRightDirection() const
{
	return FollowCam->GetRightVector();
}

FVector AKillerCharacter::GetLookForwardDirection() const
{
	return FollowCam->GetForwardVector();
}

FVector AKillerCharacter::GetMoveForwardDirection() const
{
	return FVector::CrossProduct(GetLookRightDirection(), FVector::UpVector);
}

bool AKillerCharacter::GetIsGrounded() const
{
	return bIsGrounded;
}

bool AKillerCharacter::GetIsFalling() const
{
	return bIsFalling;
}

bool AKillerCharacter::GetIsIdle() const
{
	return bIsIdle;
}

bool AKillerCharacter::GetIsRightMoving() const
{
	return bIsLeftMoving;
}

bool AKillerCharacter::GetIsLeftMoving() const
{
	return bIsRightMoving;
}
