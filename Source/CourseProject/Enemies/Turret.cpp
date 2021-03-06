// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SceneComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    TurretRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TurretRoot"));
    SetRootComponent(TurretRoot);

    TowerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TowerRoot"));
    TowerRoot->SetupAttachment(TurretRoot);

    CannonRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CannonRoot"));
    CannonRoot->SetupAttachment(TowerRoot);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

