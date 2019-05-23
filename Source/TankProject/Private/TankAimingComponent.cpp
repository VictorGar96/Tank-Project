// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"
#include "GameFramework/PlayerController.h"

//#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelSet)
{
	barrel = barrelSet;
}


void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
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
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		auto tankName = GetOwner()->GetName();

		/// Move Barrel
		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	/// Work-out difference between current barrel rotation and aimDirection

	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotatot = aimDirection.Rotation();
	auto deltaRotator = aimAsRotatot - barrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *aimAsRotatot.ToString());

	barrel->Elevate(deltaRotator.Pitch);

}


