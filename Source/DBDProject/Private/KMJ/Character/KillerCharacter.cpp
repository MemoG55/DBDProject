// Fill out your copyright notice in the Description page of Project Settings.

#include "KMJ/Character/KillerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/DataAsset/DA_KillerInput.h"

AKillerCharacter::AKillerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//HeadMesh->SetupAttachment(GetRootComponent());
	
	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	KillerAbilitySystemComponent = CreateDefaultSubobject<UKillerAbilitySystemComponent>(TEXT("KillerAbilitySystemComponent"));
	KillerAttributeSet = CreateDefaultSubobject<UKillerAttributeSet>(TEXT("KillerAttributeSet"));

	if (KillerAttributeSet)
	{
		InitKillerAttribute();
	}
}

UAbilitySystemComponent* AKillerCharacter::GetAbilitySystemComponent() const
{
	return KillerAbilitySystemComponent;
}

void AKillerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void AKillerCharacter::InitKillerAttribute()
{
	GetCharacterMovement()->MaxWalkSpeed = KillerAttributeSet->WalkingSpeed.GetCurrentValue();
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
