// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SceneComponent.h"
#include "Components/RangeCheckComponent.h"
#include "Components/MovingMount.h"
#include "CourseProject.h"

DEFINE_LOG_CATEGORY(LogCourseProjectGameplay);

// Sets default values
ATurret::ATurret()
{
    TurretRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TurretRoot"));
    SetRootComponent(TurretRoot);

    TowerRoot = CreateDefaultSubobject<UMovingMount>(TEXT("TowerRoot"));
    TowerRoot->SetupAttachment(TurretRoot);

    CannonRoot = CreateDefaultSubobject<UMovingMount>(TEXT("CannonRoot"));
    CannonRoot->SetupAttachment(TowerRoot);

	RangeCheckComponent = CreateDefaultSubobject<URangeCheckComponent>(TEXT("RangeChecker"));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	check(RangeCheckComponent);
	check(TowerRoot);

	RangeCheckComponent->OnEnterZoneDelegate.BindUObject(this, &ATurret::OnPlayerEnterZone);
	RangeCheckComponent->OnLeaveZoneDelegate.BindUObject(this, &ATurret::OnPlayerLeaveZone);

	TowerRoot->OnUpdate       .BindUObject( this, &ATurret::UpdateTowerPassiveRotation );
	TowerRoot->OnStopMoving   .BindUObject( this, &ATurret::OnTowerStopRotation        );
	TowerRoot->OnStartMoving  .BindUObject( this, &ATurret::OnTowerStartRotation       );
	CannonRoot->OnStopMoving  .BindUObject( this, &ATurret::OnCannonStopRotation       );
}

void ATurret::OnPlayerEnterZone(AActor* NewTarget)
{
	check(TowerRoot);

	if (NewTarget == nullptr)
	{
		UE_LOG(LogCourseProjectGameplay, Log, TEXT("ATurret::OnPlayerEnterZone() : NewTarget == nullptr."));
		return;
	}

	Target = NewTarget;
	TowerRoot->OnUpdate.BindUObject(this, &ATurret::UpdateTowerFollowRotation);
}

void ATurret::OnPlayerLeaveZone()
{
	check(TowerRoot);

	Target = nullptr;

	TowerRoot->OnUpdate.BindUObject(this, &ATurret::UpdateTowerPassiveRotation);
	CannonRoot->OnUpdate.BindUObject(this, &ATurret::UpdateCannonPassiveRotation);
}

void ATurret::UpdateTowerFollowRotation(float Delta)
{
	check(TowerRoot);

	if (Target == nullptr)
	{
		UE_LOG(LogCourseProjectGameplay, Log, TEXT("ATurret::OnUpdateFollowRotation() : Target == nullptr."));
		return;
	}

	FVector VectorToTarget = Target->GetActorLocation() - TowerRoot->GetComponentLocation();
	VectorToTarget.Normalize();

	const FRotator InterpRotator = FMath::RInterpConstantTo(TowerRoot->GetRelativeRotation(), VectorToTarget.Rotation(), Delta, RotationSpeed);
	TowerRoot->SetRelativeRotation(FRotator(0.f, InterpRotator.Yaw, 0.f));
}

void ATurret::UpdateTowerPassiveRotation(float Delta)
{
	check(TowerRoot);
	TowerRoot->AddRelativeRotation(FRotator(0.f, Delta * RotationSpeed, 0.f));
}

void ATurret::OnTowerStopRotation()
{
	check(CannonRoot);
	CannonRoot->OnUpdate.BindUObject(this, &ATurret::UpdateCannonFollowRotation);
}

void ATurret::OnTowerStartRotation()
{
	check(CannonRoot);
	CannonRoot->OnUpdate.Unbind();
}

void ATurret::UpdateCannonFollowRotation(float Delta)
{
	check(CannonRoot);

	if (Target == nullptr)
	{
		UE_LOG(LogCourseProjectGameplay, Log, TEXT("ATurret::UpdateCannonFollowRotation() : Target == nullptr."));
		return;
	}

	FVector VectorToTarget = Target->GetActorLocation() - CannonRoot->GetComponentLocation();
	VectorToTarget.Normalize();

	const FRotator InterpRotator = FMath::RInterpConstantTo(CannonRoot->GetRelativeRotation(), VectorToTarget.Rotation(), Delta, RotationSpeed);
	CannonRoot->SetRelativeRotation(FRotator(InterpRotator.Pitch, 0.f, 0.f));
}

void ATurret::UpdateCannonPassiveRotation(float Delta)
{
	check(CannonRoot);

	const FRotator InterpRotator = FMath::RInterpConstantTo(CannonRoot->GetRelativeRotation(), FVector::ForwardVector.Rotation(), Delta, RotationSpeed);
	CannonRoot->SetRelativeRotation(FRotator(InterpRotator.Pitch, 0.f, 0.f));
}

void ATurret::OnCannonStopRotation()
{
	check(CannonRoot);

	if (!Target)
	{
		CannonRoot->OnUpdate.Unbind();
		return;
	}

	/** Shoot! */
}

