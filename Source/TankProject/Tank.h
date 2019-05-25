// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;

UCLASS()
class TANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties


	UFUNCTION(BlueprintCallable, Category = SetUp)
	void SetBarrelReference(UTankBarrel* barrelToset);

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void SetTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector hitLocation) const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* tankAimingComponent = nullptr;

private:
	ATank();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 100000.f; /// TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTime = 1.f; /// TODO find sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	TSubclassOf<AProjectile> projectileBlueprint;

	UTankBarrel* barrel = nullptr;


	float reloadTankInSeconds = 2.f;

	double lastFireTime = 0;

};
