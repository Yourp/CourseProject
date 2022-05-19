// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class USceneComponent;

UCLASS()
class ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    USceneComponent* TurretRoot;
    
    UPROPERTY(EditAnywhere)
    USceneComponent* TowerRoot;

    UPROPERTY(EditAnywhere)
    USceneComponent* CannonRoot;
};
