// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MovingMount.generated.h"

DECLARE_DELEGATE_OneParam(FOnUpdate, float);
DECLARE_DELEGATE(FOnStopMoving);
DECLARE_DELEGATE(FOnStartMoving);

/** A component that checks its own motion and raises the appropriate events. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMovingMount : public USceneComponent
{
    GENERATED_BODY()

public:	
	/** Sets default values for this component's properties. */
    UMovingMount();

    /** Calling in every frame. */
    FOnUpdate       OnUpdate;

    /** Called when the component has stopped. */
    FOnStopMoving   OnStopMoving;

    /** Called when the component has started moving. */
    FOnStartMoving  OnStartMoving;

    /** Returns true if the component is currently moving. */
    FORCEINLINE bool IsMoving() const { return bIsMoving; }

    /** Called every frame. */
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:


private:

    /** True if the component is currently moving. */
    bool bIsMoving = false;
};
