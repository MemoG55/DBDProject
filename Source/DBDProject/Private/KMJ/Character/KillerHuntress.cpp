// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Character/KillerHuntress.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/Axe/AxeComponent.h"
#include "KMJ/Axe/GenericPool.h"
#include "KMJ/GAS/GA_Skill.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"

AKillerHuntress::AKillerHuntress()
{
	HuntressAttributeSet = CreateDefaultSubobject<UHuntressAttributeSet>(TEXT("HuntressAttributeSet"));
	AxeComponent = CreateDefaultSubobject<UAxeComponent>(TEXT("AxeComponent"));

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeapon"));
	RightWeapon->SetupAttachment(GetMesh(), TEXT("RightWeapon"));
	LeftAxe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftAxe"));
	LeftAxe->SetupAttachment(GetMesh(), FName(TEXT("LeftAxe")));
}

void AKillerHuntress::InitHuntressAttribute()
{
	if (!KillerAttributeSet) return;
	if (HasAuthority())
	{
		if (KillerAttributeSet)
		{
			float NewSpeed = KillerAttributeSet->GetCurrentWalkingSpeed();
		
			//UE_LOG(LogTemp, Warning, TEXT("[Server] InitHuntressAttribute WalkingSpeed: %.1f"), NewSpeed);
			ReplicatedWalkSpeed = NewSpeed; 

			GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
			AxeComponent->InitProjectilePool(HuntressAttributeSet->AxeNumber.GetCurrentValue());
		}
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		float NewSpeed = KillerAttributeSet->GetCurrentWalkingSpeed();
		//UE_LOG(LogTemp, Warning, TEXT("[Client] InitHuntressAttribute WalkingSpeed: %.1f"), NewSpeed);
	}
}

void AKillerHuntress::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AKillerHuntress::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKillerHuntress::PawnClientRestart()
{
	Super::PawnClientRestart();
}

void AKillerHuntress::OnGameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	InitHuntressAttribute();
}

void AKillerHuntress::ServerSideInit()
{
	Super::ServerSideInit();
	KillerAbilitySystemComponent->InitAbilityActorInfo(this, this);
	//UE_LOG(LogTemp, Warning, TEXT("0. [Server] InitHuntressAttribute WalkingSpeed: %.1f"), GetCharacterMovement()->MaxWalkSpeed);
	KillerAbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.AddUObject(
		this, &AKillerHuntress::OnGameplayEffectApplied);
	//UE_LOG(LogTemp, Warning, TEXT("1. [Server] InitHuntressAttribute WalkingSpeed: %.1f"), GetCharacterMovement()->MaxWalkSpeed);
	KillerAbilitySystemComponent->ApplyInitializeEffects();
	//UE_LOG(LogTemp, Warning, TEXT("2. [Server] InitHuntressAttribute WalkingSpeed: %.1f"), GetCharacterMovement()->MaxWalkSpeed);
	InitHuntressAttribute();
	//UE_LOG(LogTemp, Warning, TEXT("3. [Server] InitHuntressAttribute WalkingSpeed: %.1f"), GetCharacterMovement()->MaxWalkSpeed);
}

void AKillerHuntress::ClientSideInit()
{
	Super::ClientSideInit();
	KillerAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AKillerHuntress::BeginPlay()
{
	Super::BeginPlay();
	KillerAttributeSet->OnWalkingSpeedChanged.AddDynamic(this, &AKillerHuntress::OnWalkingSpeedChanged);
	UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(this, DBDGameplayTags::Killer_Huntress_Status_AxeFull);
	//OnItemUIInitialize.Broadcast(this, EPlayerRole::Killer);
	if (IsLocallyControlled())
	{
		FTimerHandle BroadcastHandle;
		GetWorldTimerManager().SetTimer(
			BroadcastHandle,
			[this]()
			{
				if (IsValid(this))
				{
					// JMS: UI수정: WidgetComponent에서 스폰 시 초기화
					// OnItemUIInitialize.Broadcast(this, EPlayerRole::Killer);
				}
			},
			5.0f,   // Delay 5 seconds
			false   // 반복 안 함
		);
	}
}

void AKillerHuntress::OnRep_WalkSpeedChanged()
{
	//Debug::Print(FString::Printf(TEXT("AKillerHuntress::OnRep_WalkSpeedChanged: %f"), ReplicatedWalkSpeed), 31);
	GetCharacterMovement()->MaxWalkSpeed = ReplicatedWalkSpeed;
}

void AKillerHuntress::OnWalkingSpeedChanged(float NewWalkingSpeed)
{
	//Debug::Print(FString::Printf(TEXT("AKillerHuntress::OnWalkingSpeedChanged: %f"), ReplicatedWalkSpeed), 32);
	ReplicatedWalkSpeed = NewWalkingSpeed;
}

void AKillerHuntress::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AKillerHuntress, ReplicatedWalkSpeed, COND_None, REPNOTIFY_Always);
}

void AKillerHuntress::Multicast_SetLeftAxeVisibility_Implementation(bool bVisible)
{
	if (LeftAxe)
	{
		LeftAxe->SetVisibility(bVisible);
	}
}
