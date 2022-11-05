// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class USceneComponent;
class URangeCheckComponent;
class UMovingMount;

UCLASS()
class ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    USceneComponent* TurretRoot = nullptr;
    
    UPROPERTY(EditAnywhere)
	UMovingMount* TowerRoot = nullptr;

    UPROPERTY(EditAnywhere)
    UMovingMount* CannonRoot = nullptr;

	UPROPERTY(EditAnywhere)
    URangeCheckComponent* RangeCheckComponent = nullptr;

	UPROPERTY()
	AActor* Target = nullptr;

	UPROPERTY(EditAnywhere)
    float RotationSpeed = 60.f;

	void OnPlayerEnterZone(AActor* NewTarget);
	void OnPlayerLeaveZone();

	void UpdateTowerFollowRotation(float Delta);
	void UpdateTowerPassiveRotation(float Delta);
	void OnTowerStopRotation();
	void OnTowerStartRotation();

	void UpdateCannonFollowRotation(float Delta);
	void UpdateCannonPassiveRotation(float Delta);
	void OnCannonStopRotation();
};
