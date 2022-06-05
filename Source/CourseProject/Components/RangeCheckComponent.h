// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RangeCheckComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnEnterZone, AActor const*);
DECLARE_DELEGATE(FOnLeaveZone);

/** The component checks the distance to the target with a certain frequency and calls the appropriate events. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class URangeCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties. */
	URangeCheckComponent();

    /** Called when the target has entered the trigger area. */
    FOnEnterZone OnEnterZoneDelegate;

    /** Called when the target has exited the trigger area. */
    FOnLeaveZone OnLeaveZoneDelegate;

    /** Actual distance to exit the trigger area. */
    FORCEINLINE float GetExitRadius() const { return EntryRadius + AdditionalExitRadius; }

protected:

	/** Called when the game starts. */
	virtual void BeginPlay() override;

private:

    /** Distance check timer. */
    FTimerHandle TimerOfUpdate;

    /** Trigger zone radius. */
    UPROPERTY(EditAnywhere, Category = "Range")
    float EntryRadius           = 500.f;

    /** Distance that is added to the trigger zone radius to determine the exit distance from this zone. */
    UPROPERTY(EditAnywhere, Category = "Range")
    float AdditionalExitRadius  = 200.f;

    /** Time in seconds after which the distance to the target will be checked. */
    UPROPERTY(EditAnywhere)
    float DelayOfCheck          = 0.2f;

    /** To this target we will check the distance. */
    UPROPERTY()
    AActor* Target              = nullptr;

    /** Cyclically called while the target is outside the trigger zone. */
    void UpdateOutOfZone();

    /** Cyclically called while the target is in the trigger zone. */
    void UpdateInZone();
};
