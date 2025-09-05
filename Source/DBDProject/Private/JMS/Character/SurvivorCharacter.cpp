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

ASurvivorCharacter::ASurvivorCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.0f, 0.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

void ASurvivorCharacter::AbilityInput(const FInputActionValue& InputActionValue, ESurvivorAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)InputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)InputID);
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

void ASurvivorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASurvivorCharacter::AddUniqueTag(FGameplayTag Tag)
{
	ServerAddUniqueTag(Tag);
}

void ASurvivorCharacter::RemoveTag(FGameplayTag Tag)
{
	ServerRemoveTag(Tag);
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
	if (GetAbilitySystemComponent()->HasMatchingGameplayTag(Tag))
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
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag);
	GetAbilitySystemComponent()->RemoveReplicatedLooseGameplayTag(Tag);
}

void ASurvivorCharacter::ServerAddUniqueTag_Implementation(const FGameplayTag& Tag)
{
	if (!GetAbilitySystemComponent()->HasMatchingGameplayTag(Tag))
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(Tag);
		GetAbilitySystemComponent()->AddReplicatedLooseGameplayTag(Tag);
	}
}
