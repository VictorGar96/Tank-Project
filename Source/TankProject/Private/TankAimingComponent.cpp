// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Gameframework/Actor.h"
#include "GameFramework/PlayerController.h"

//#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	/// First fire is after first reload
	lastFireTime = GetWorld()->GetRealTimeSeconds();

}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((GetWorld()->GetRealTimeSeconds() - lastFireTime) < reloadTankInSeconds)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reloading red"));

		state = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming"));
		state = EFiringState::Aiming;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Locked"));
		state = EFiringState::Locked;
	}
}
 
void UTankAimingComponent::Initialise(UTankBarrel * tankBarrelToSet, UTankTurret * tankTurretToSet)
{
	if (!tankBarrelToSet || !tankTurretToSet) { return; }

	barrel = tankBarrelToSet;
	turret = tankTurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel)) { return false; }

	auto barrelForwardVector = barrel->GetForwardVector();
	
	/// Returns true or false weather the barrelForwardVector is equal to aimDir
	return !barrelForwardVector.Equals(aimDir, 0.01);

}

void UTankAimingComponent::AimAt(FVector hitLocation) 
{
	///auto ourTankName = GetOwner()->GetName();
	///auto barrelLocation = barrel->GetComponentLocation().ToString();
	
	if (!barrel) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	/// Calculate the outLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace /// Allows to trace the projectile curve
	);

	if (bHaveAimSolution)
	{
		aimDir = outLaunchVelocity.GetSafeNormal();

		/// Move Barrel
		MoveBarrelTowards(aimDir);
		
		/*auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);*/
	}
	//else
	//{
	//	/*auto time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);*/
	//}

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	/// Work-out difference between current barrel rotation and aimDirection

	if (!barrel || !turret) { return; }

	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotatot = aimDirection.Rotation();
	auto deltaRotator = aimAsRotatot - barrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *aimAsRotatot.ToString());

	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{

	//if (!(barrel && projectileBlueprint)) { return; }

	/// Returns a double

	if (state != EFiringState::Reloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired projectile"));

		/// Spawn projectile 
		if (!ensure(barrel)) { return; }
		if (!ensure(projectileBlueprint)) { return; }

		auto projectile = GetWorld()->SpawnActor<AProjectile>(
				projectileBlueprint,
				barrel->GetSocketLocation(FName("Projectile")),
				barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(launchSpeed);
		
		lastFireTime = GetWorld()->GetRealTimeSeconds();

	}


}






