// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBDEnum.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "DBDBlueprintFunctionLibrary.generated.h"

class ADBDCharacter;
class UAbilitySystemComponent;
class UGameplayEffect;
class UDBDAbilitySystemComponent;
struct FGameplayTag;

UENUM()
enum class EBaseConfirmType : uint8
{
	Yes,
	No,
};

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UDBDAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	// 서버에서 실행
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddUniqueTagToActor(AActor* Actor, FGameplayTag Tag);

	// 서버에서 실행
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void RemoveTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary",
		meta=(DisplayName="Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void ApplyGameplayEffectToTargetActor(AActor* TargetActor, AActor* SourceActor,
	                                             TSubclassOf<UGameplayEffect> GameplayEffectClass,
	                                             int level);
	// 상호작용 시 액터가 어디붙어있는지 확인용도
	static FGameplayTag ComputeInteractDirection(const AActor* Object, const AActor* Interactor);

	// 캐릭터가 생존자인지 살인마인지 판단 해서 Enum반환
	static EPlayerRole GetPlayerRole(const AActor* Actor);

	// 캐릭터가 생존자인지?
	static bool IsSurvivor(const AActor* Actor);

	// 캐릭터가 살인마인지?
	static bool IsKiller(const AActor* Actor);

	// ASC에서 모든 하위 태그 제거 - 서버에서 실행
	static void RemoveAllSubTags(FName TagMask, UAbilitySystemComponent* TargetASC);

	// 캐릭터 메시의 루트를 메시의 소켓에 부착
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AttachDBDCharacterToMeshSocket(USkeletalMeshComponent* Mesh, FName MeshSocket, ADBDCharacter* Character,
	                                           FName CharacterSocket = FName("joint_Char"));
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AttachCharacterWithRotationAdjust(USkeletalMeshComponent* Mesh, FName MeshSocket, ADBDCharacter* Character, FRotator Offset,
	                                              FName CharacterSocket = FName("joint_Char"));
};
