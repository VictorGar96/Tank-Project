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

	auto tankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Donkey %s: BP_Construct"), *tankName);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	auto tankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Donkey %s: BP_Begin"), *tankName);

}

void ATank::AimAt(FVector hitLocation) const
{
	if (!tankAimingComponent) { return; }

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


