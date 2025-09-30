// Fill out your copyright notice in the Description page of Project Settings.
// JMS: 사망 후 화면을 제공할 카메라 액터입니다.
// TODO: 사망시 키 입력으로 회전, 다음 플레이어 화면으로 전환
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBDSpectatorCam.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DBDPROJECT_API ADBDSpectatorCam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBDSpectatorCam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	UCameraComponent* CameraComponent;
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;
	
};
