// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingMount.h"

UMovingMount::UMovingMount()
{
    /**
     * Set this component to be initialized when the game starts, and to be ticked every frame.
     * You can turn these features off to improve performance if you don't need them.
     */
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovingMount::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const FTransform OldTransform = GetRelativeTransform();

    OnUpdate.ExecuteIfBound(DeltaTime);

    if (GetRelativeTransform().Equals(OldTransform))
    {
        if (bIsMoving)
        {
            bIsMoving = false;
            OnStopMoving.ExecuteIfBound();
        }
    }
    else if (bIsMoving == false)
    {
        bIsMoving = true;
        OnStartMoving.ExecuteIfBound();
    }
}

