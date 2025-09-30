// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Character/KillerHuntress.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/GAS/GA_Skill.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDDebugHelper.h"

AKillerHuntress::AKillerHuntress()
{
	HuntressAttributeSet = CreateDefaultSubobject<UHuntressAttributeSet>(TEXT("HuntressAttributeSet"));
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
	//TODO::IA_Killer_Skill의 Trigger GA_Skill과 연동
	/*if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		IA_Killer_Skill.
		EnhancedInput->BindAction(IA_Killer_Skill, ETriggerEvent::Triggered, this, &AKillerHuntress::OnKillerSkillPressed);
		
	}*/
	KillerAttributeSet->OnWalkingSpeedChanged.AddDynamic(this, &AKillerHuntress::OnWalkingSpeedChanged);
}
/*
void AKillerHuntress::OnKillerSkillPressed()
{
	if (KillerAbilitySystemComponent)
	{
		TSubclassOf<UGameplayAbility> SkillAbilityClass = UGA_Skill::StaticClass();
		TArray<FGameplayAbilitySpec> AbilitySpecs = KillerAbilitySystemComponent->GetActivatableAbilities();

		for (const FGameplayAbilitySpec& AbilitySpec : AbilitySpecs)
		{
			if (AbilitySpec.Ability->GetClass() == SkillAbilityClass)
			{
				if (UGA_Skill* SkillAbility = Cast<UGA_Skill>(SkillAbilityClass)) SkillAbility->OnPressed();
				return;
			}
		}
	}
}
*/

void AKillerHuntress::OnRep_WalkSpeedChanged()
{
	Debug::Print(FString::Printf(TEXT("AKillerHuntress::OnRep_WalkSpeedChanged: %f"), ReplicatedWalkSpeed), 31);
	GetCharacterMovement()->MaxWalkSpeed = ReplicatedWalkSpeed;
}

void AKillerHuntress::OnWalkingSpeedChanged(float NewWalkingSpeed)
{
	Debug::Print(FString::Printf(TEXT("AKillerHuntress::OnWalkingSpeedChanged: %f"), ReplicatedWalkSpeed), 32);
	ReplicatedWalkSpeed = NewWalkingSpeed;
}

void AKillerHuntress::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AKillerHuntress, ReplicatedWalkSpeed, COND_None, REPNOTIFY_Always);
}
