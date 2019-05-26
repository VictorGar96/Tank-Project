// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.generated.h"

/// Enum for aiming state
UENUM()
enum class EFiringState : uint8 
{	
	Locked, 
	Aiming, 
	Reloading 
};

// Holds barrel properties and Elevation method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState state = EFiringState::Aiming;

public:	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* tankBarrelToSet, UTankTurret* tankTurretToSet);
	
	void AimAt(FVector hitLocation, float launchSpeed);
	
	// TODO add SetTurretReference

private:
	
	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;


	void MoveBarrelTowards(FVector aimDirection);
};
