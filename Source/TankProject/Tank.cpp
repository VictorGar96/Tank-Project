// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	tankAimingComponent->SetBarrelReference(barrelToSet);

	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
	tankAimingComponent->SetTurretReference(turretToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation) const
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
						/// Returns a double
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTankInSeconds;

	if (barrel && isReloaded) 
	{ 
		/// Spawn projectile 

		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")), 
			barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(launchSpeed);
	
		lastFireTime = FPlatformTime::Seconds();
	}


}


