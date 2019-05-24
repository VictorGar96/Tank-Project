// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "TankTurret.h"
#include "TankAimingComponent.generated.h"

// Holds barrel properties and Elevation method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	

public:	
	
	void AimAt(FVector hitLocation, float launchSpeed);
	
	void SetBarrelReference(UTankBarrel* barrelSet);

	void SetTurretReference(UTankTurret* turretSet);
	
	void MoveBarrelTowards(FVector aimDirection);

	// TODO add SetTurretReference

private:
	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;

	UTankTrack* track = nullptr;
};
