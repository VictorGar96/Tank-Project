// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.generated.h"

class AProjectile;

/// Enum for aiming state
UENUM()
enum class EFiringState : uint8 
{	
	Locked, 
	Aiming, 
	Reloading,
	OutOfAmmo
};

// Holds barrel properties and Elevation method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector aimDirection);

	EFiringState GetFiringState() const;

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState state = EFiringState::Reloading;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

public:	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* tankBarrelToSet, UTankTurret* tankTurretToSet);
	
	void AimAt(FVector hitLocation);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 10000.f; /// TODO find sensible default
	// TODO add SetTurretReference

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 roundsLeft = 10;


	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

private:
	

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTime = 1.f; /// TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	TSubclassOf<AProjectile> projectileBlueprint;
	
	float reloadTankInSeconds = 0.1f;

	double lastFireTime = 0;

	FVector aimDir;

};
