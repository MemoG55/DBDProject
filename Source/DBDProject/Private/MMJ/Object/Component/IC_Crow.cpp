// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Crow.h"

#include "Shared/Character/DBDCharacter.h"

UIC_Crow::UIC_Crow()
{
}

void UIC_Crow::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                  SweepResult);
	
	if (ADBDCharacter* Character = Cast<ADBDCharacter>(OtherActor))
	{
		if (CanInteraction(Character))
		{
			StartInteraction(OtherActor);
		}
	}
}

void UIC_Crow::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (ADBDCharacter* Character = Cast<ADBDCharacter>(OtherActor))
	{
		UnSetInteractors(OtherActor);
	}
}

void UIC_Crow::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);
}

void UIC_Crow::FinishInteraction(AActor* Actor)
{
	CompleteInteraction(Actor);

	// 착지하는 시간(약 5초)이후 타이머를 실행해서 Interactors.IsEmpty() 체크해서 주변에 있는지 감지처리
	if (!FindInteractorTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			FindInteractorTimer,
			this,
			&ThisClass::FindInteractor,
			5.f,
			false);
	}
}

void UIC_Crow::FindInteractor()
{
	if (!InteractedActors.IsEmpty())
	{
		StartInteraction(InteractedActors.Last());
	}
	GetWorld()->GetTimerManager().ClearTimer(FindInteractorTimer);
	FindInteractorTimer.Invalidate();
}
