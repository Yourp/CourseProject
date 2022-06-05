// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeCheckComponent.h"

// Called when the game starts
void URangeCheckComponent::BeginPlay()
{
    UWorld* World = GetWorld();
    check(World);

    Target = Cast<AActor>(UGameplayStatics::GetPlayerPawn(World, 0));
    check(Target);

    Super::BeginPlay();

    World->GetTimerManager().SetTimer(TimerOfUpdate, this, &URangeCheckComponent::UpdateOutOfZone, DelayOfCheck, true);
}

void URangeCheckComponent::UpdateOutOfZone()
{
    float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Target->GetActorLocation());

    if (Distance < EntryRadius)
    {
        OnEnterZoneDelegate.ExecuteIfBound(Target);
        GetWorld()->GetTimerManager().SetTimer(TimerOfUpdate, this, &URangeCheckComponent::UpdateInZone, DelayOfCheck, true);
    }
}

void URangeCheckComponent::UpdateInZone()
{
    float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Target->GetActorLocation());

    if (Distance >= GetExitRadius())
    {
        OnLeaveZoneDelegate.ExecuteIfBound();
        GetWorld()->GetTimerManager().SetTimer(TimerOfUpdate, this, &URangeCheckComponent::UpdateOutOfZone, DelayOfCheck, true);
    }
}

