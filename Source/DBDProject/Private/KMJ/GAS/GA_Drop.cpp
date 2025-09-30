// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Drop.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/GA/Passive/GA_SurvivorCapturedByKiller.h"
#include "KMJ/Character/KillerCharacter.h"

void UGA_Drop::SetSurvivorGAClearAndDetach(AActor* Killer)
{
    AKillerCharacter* KillerCharacter = Cast<AKillerCharacter>(Killer);
    if (KillerCharacter)
    {
        UAbilitySystemComponent* ASC = KillerCharacter->GetCarriedSurvivorCharacter()->GetAbilitySystemComponent();

        if (ASC)
        {
            const FGameplayAbilitySpec* MatchingSpec = nullptr;

            // ASC에 등록된 모든 AbilitySpec을 순회
            for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
            {
                if (Spec.Ability && Spec.Ability->IsA(UGA_SurvivorCapturedByKiller::StaticClass()))
                {
                    if (Spec.IsActive())
                    {
                        ASC->CancelAbility(Spec.Ability);
                        break; // 하나만 종료하고 끝내려면 break
                    }
                }
            }
        }

    }
    else return;
}



