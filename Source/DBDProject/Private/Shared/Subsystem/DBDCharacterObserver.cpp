// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Subsystem/DBDCharacterObserver.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/ScratchMark/PoolEntry_ScratchMark.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDGameMode.h"
#include "Shared/GameFramework/DBDGameStateBase.h"
#include "Shared/ObjectPool/GenericObjectPool.h"
#include "Shared/Subsystem/DBDAuraSubsystem.h"


void UDBDCharacterObserver::RegisterKiller(AKillerCharacter* KillerCharacter)
{
	Killer = KillerCharacter;

	// TODO :: 로비�면 만들곸원�만채워졌을 �의 �수�바인�전 �요.
	if (KillerCharacter->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->Killer = KillerCharacter;
			BindingPlayerCharacter(KillerCharacter);

			if (UDBDAuraSubsystem* AuraSystem = GetWorld()->GetSubsystem<UDBDAuraSubsystem>())
			{
				for (AObj_Generator* Generator : DBDGameState->Generators)
				{
					AuraSystem->SetAuraState(Generator, KillerCharacter->GetPlayerState(), 1);
				}
			}
		}
	}
}

void UDBDCharacterObserver::UnregisterKiller(AKillerCharacter* KillerCharacter)
{
	if (Killer == KillerCharacter)
	{
		Killer = nullptr;
	}

	// TODO :: 로비�면 만들곸원�만채워졌을 �의 �수�바인�전 �요.
	if (KillerCharacter->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			if (DBDGameState->Killer == KillerCharacter)
			{
				DBDGameState->Killer = nullptr;
				UnBindingPlayerCharacter(KillerCharacter);
			}
		}
	}
}

void UDBDCharacterObserver::RegisterSurvivor(ASurvivorCharacter* SurvivorCharacter)
{
	Survivors.AddUnique(SurvivorCharacter);
	
	if (SurvivorCharacter->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->Survivors.AddUnique(SurvivorCharacter);
			BindingPlayerCharacter(SurvivorCharacter);
		}
	}
}

void UDBDCharacterObserver::UnregisterSurvivor(ASurvivorCharacter* SurvivorCharacter)
{
	Survivors.Remove(SurvivorCharacter);

	// TODO :: 로비�면 만들곸원�만채워졌을 �의 �수�바인�전 �요.
	if (SurvivorCharacter->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->Survivors.Remove(SurvivorCharacter);
			UnBindingPlayerCharacter(SurvivorCharacter);
		}
	}
}

void UDBDCharacterObserver::PrintAllCharacter()
{
	if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	{
		if (DBDGameState->Killer)
		{
			UE_LOG(LogTemp, Warning, TEXT("JMS : UDBDCharacterObserver : Killer : %s"),
			       *DBDGameState->Killer->GetName());
		}
		for (ASurvivorCharacter* Survivor : DBDGameState->Survivors)
		{
			UE_LOG(LogTemp, Warning, TEXT("JMS : UDBDCharacterObserver : Survivor : %s"), *Survivor->GetName());
		}
	}
}

AKillerCharacter* UDBDCharacterObserver::GetKiller() const
{
	return Killer;

	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	if (DBDGameState->Killer)
	// 	{
	// 		return DBDGameState->Killer;
	// 	}
	// }
}

ASurvivorCharacter* UDBDCharacterObserver::GetSurvivorByIndex(int32 Index) const
{
	return Survivors[Index];

	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	if (DBDGameState->Survivors.IsValidIndex(Index))
	// 	{
	// 		return DBDGameState->Survivors[Index];
	// 	}
	// }
}

TArray<ASurvivorCharacter*> UDBDCharacterObserver::GetSurvivors()
{
	return Survivors;
	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	return DBDGameState->Survivors;
	// }
}
// JMS : 거리와 조건 태그들을 활용해 생존자의 오라를 활성화(EX: SelfCare, Bond)
void UDBDCharacterObserver::EnableSurvivorAuraWithDistanceAndTag(ADBDCharacter* EffectOwner, float Distance,
                                                                 FGameplayTagContainer RequiredTags,
                                                                 FGameplayTagContainer BlockedTags)
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UDBDCharacterObserver::ShowAuraAfterCheckSurvivorDistanceAndTag, EffectOwner,
	                          Distance,
	                          RequiredTags, BlockedTags);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate,
	                                       AuraRefreshInterval, true);
	AuraTimerHandles.Add(TimerHandle);
}

void UDBDCharacterObserver::ApplyGEWithSurvivorWithinDistance(ADBDCharacter* Target, float Distance,
                                                              TSubclassOf<UGameplayEffect> GE)
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UDBDCharacterObserver::CheckSurvivorDistanceAndApplyEffect, Target,
	                          Distance, GE);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate,
	                                       ApplyGEToSelfDistanceCheckInterval, true);
	DistanceCheckTimerHandles.Add(TimerHandle);
}

void UDBDCharacterObserver::ApplyGEToSurvivorsWithinDistance(ADBDCharacter* EffectOwner, float Distance,
                                                             TSubclassOf<UGameplayEffect> GE)
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UDBDCharacterObserver::CheckDistanceAndRefreshEffectToOthers, EffectOwner,
	                          Distance, GE);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate,
	                                       ApplyGEToOthersDistanceCheckInterval, true);
	DistanceCheckTimerHandles.Add(TimerHandle);
}

void UDBDCharacterObserver::ShowAuraAfterCheckSurvivorDistanceAndTag(ADBDCharacter* EffectOwner, float Distance,
                                                                     FGameplayTagContainer RequiredTags,
                                                                     FGameplayTagContainer BlockedTags)
{
	for (ASurvivorCharacter* Survivor : Survivors)
	{
		if ((RequiredTags.Num() <= 0 || Survivor->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(RequiredTags))
			&&
			!Survivor->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(BlockedTags) &&
			Survivor->GetDistanceTo(EffectOwner) <= Distance && Survivor != EffectOwner)
		{
			Survivor->EnableAura(1);
		}
		else
		{
			Survivor->DisableAura();
		}
	}
}

void UDBDCharacterObserver::CheckSurvivorDistanceAndApplyEffect(ADBDCharacter* Target, float Distance,
                                                                TSubclassOf<UGameplayEffect> GE)
{
	int32 SurvivorCount = 0;
	Target->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(
		GE, Target->GetAbilitySystemComponent());
	TArray<ASurvivorCharacter*> NearbySurvivors;
	for (ASurvivorCharacter* Survivor : Survivors)
	{
		if (Survivor != Target && Survivor->GetDistanceTo(Target) <= Distance)
		{
			NearbySurvivors.Add(Survivor);
		}
	}
	if (NearbySurvivors.Num() > 0)
	{
		FGameplayEffectContextHandle ContextHandle = Target->GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = Target->GetAbilitySystemComponent()->MakeOutgoingSpec(
			GE, static_cast<float>(NearbySurvivors.Num()),
			ContextHandle);
		for (ASurvivorCharacter* Survivor : NearbySurvivors)
		{
			Target->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToTarget(
				EffectSpecHandle, Survivor->GetAbilitySystemComponent());
		}
		Target->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(
			EffectSpecHandle);
	}
}

void UDBDCharacterObserver::CheckDistanceAndRefreshEffectToOthers(ADBDCharacter* EffectOwner, float Distance,
                                                                  TSubclassOf<UGameplayEffect> GE)
{
	for (ASurvivorCharacter* Survivor : Survivors)
	{
		if (Survivor != EffectOwner && Survivor->GetDistanceTo(EffectOwner) <= Distance)
		{
			FGameplayEffectContextHandle ContextHandle = EffectOwner->GetAbilitySystemComponent()->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = EffectOwner->GetAbilitySystemComponent()->MakeOutgoingSpec(
				GE, 0,
				ContextHandle);
			EffectOwner->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToTarget(
				EffectSpecHandle, Survivor->GetAbilitySystemComponent());
		}
	}
}

void UDBDCharacterObserver::EnableScratchMarkOnEverySurvivor()
{
	for (ASurvivorCharacter* Survivor : Survivors)
	{
		Survivor->SprintTagUpdateDelegate.AddDynamic(this, &UDBDCharacterObserver::LeaveScratchMarkOnSurvivorSprint);
	}
}

void UDBDCharacterObserver::EnableScratchMarkOnCurrentSurvivor(ASurvivorCharacter* Survivor)
{
	if (Survivor)
	{
		Survivor->SprintTagUpdateDelegate.AddDynamic(this, &UDBDCharacterObserver::LeaveScratchMarkOnSurvivorSprint);
	}
}

void UDBDCharacterObserver::BindingPlayerCharacter(ADBDCharacter* Player)
{
	if (AKillerCharacter* KillerCharacter = Cast<AKillerCharacter>(Player))
	{
		if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (KillerCharacter->GetAbilitySystemComponent())
			{
				KillerCharacter->GetAbilitySystemComponent()->RegisterGameplayTagEvent(DBDGameplayTags::Killer_Common_Status_Carrying,
					EGameplayTagEventType::NewOrRemoved)
				.AddUObject(DBDGameMode, &ADBDGameMode::OnKillerTagChange);
			}
		}
	}
	else
	{
		if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent())
			{
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Dying,
				                              EGameplayTagEventType::NewOrRemoved)
				   .AddUObject(DBDGameMode, &ADBDGameMode::OnSurvivorTagChange);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Captured_Killer,
				                              EGameplayTagEventType::NewOrRemoved)
				   .AddUObject(DBDGameMode, &ADBDGameMode::OnSurvivorTagChange);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Captured_Hook,
				                              EGameplayTagEventType::NewOrRemoved)
				   .AddUObject(DBDGameMode, &ADBDGameMode::OnSurvivorTagChange);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Dead,
				                              EGameplayTagEventType::NewOrRemoved)
				   .AddUObject(DBDGameMode, &ADBDGameMode::OnSurvivorTagChange);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Escaped,
				                              EGameplayTagEventType::NewOrRemoved)
				   .AddUObject(DBDGameMode, &ADBDGameMode::OnSurvivorTagChange);
			}
		}
	}
}

void UDBDCharacterObserver::UnBindingPlayerCharacter(ADBDCharacter* Player)
{
	if (AKillerCharacter* KillerCharacter = Cast<AKillerCharacter>(Player))
	{
		if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (KillerCharacter->GetAbilitySystemComponent())
			{
				KillerCharacter->GetAbilitySystemComponent()->RegisterGameplayTagEvent(DBDGameplayTags::Killer_Common_Status_Carrying, EGameplayTagEventType::NewOrRemoved)
				.RemoveAll(DBDGameMode);
			}
		}
	}
	else
	{
		if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent())
			{
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Dying,
				                              EGameplayTagEventType::NewOrRemoved)
				   .RemoveAll(DBDGameMode);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Captured_Killer,
				                              EGameplayTagEventType::NewOrRemoved)
				   .RemoveAll(DBDGameMode);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Captured_Hook,
				                              EGameplayTagEventType::NewOrRemoved)
				   .RemoveAll(DBDGameMode);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Dead,
				                              EGameplayTagEventType::NewOrRemoved)
				   .RemoveAll(DBDGameMode);
				ASC->RegisterGameplayTagEvent(DBDGameplayTags::Survivor_Status_Escaped,
				                              EGameplayTagEventType::NewOrRemoved)
				   .RemoveAll(DBDGameMode);
			}
		}
	}
}


void UDBDCharacterObserver::LeaveScratchMarkOnSurvivorSprint(ASurvivorCharacter* Survivor, int32 NewCount)
{
	if (NewCount > 0)
	{
		LeaveScratchMarkTimerDelegate.BindUObject(this, &UDBDCharacterObserver::SpawnScratchMarkOnSurvivorLocation,
		                                          Survivor);
		GetWorld()->GetTimerManager().SetTimer(LeaveScratchMarkTimerHandle, LeaveScratchMarkTimerDelegate,
		                                       LeaveScratchMarkInterval, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(LeaveScratchMarkTimerHandle);
		LeaveScratchMarkTimerHandle.Invalidate();
	}
}

void UDBDCharacterObserver::SpawnScratchMarkOnSurvivorLocation(ASurvivorCharacter* Survivor)
{
	APoolEntry_ScratchMark* ScratchMarkActor = Survivor->GetScratchMarkFromPool();
	ScratchMarkActor->SetActorLocation(Survivor->GetActorLocation());
	ScratchMarkActor->SetActive(true, Survivor);
}
