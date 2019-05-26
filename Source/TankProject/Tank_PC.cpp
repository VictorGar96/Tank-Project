// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PC.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "TankMovementComponent.h"
#include "../Public/TankAimingComponent.h"
#include "Engine.h"
#include "Components/ActorComponent.h"

void ATank_PC::BeginPlay()
{
	Super::BeginPlay();

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!aimingComponent) {	return;	}
		foundAimingComponent(aimingComponent);

}

void ATank_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

void ATank_PC::AimTowardsCrossHair()
{
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!aimingComponent) { return; }

	FVector hitLocation; /// OUT paremeter

	if(GetSightRayHitLocation(hitLocation)) /// LineTrace
	{
		aimingComponent->AimAt(hitLocation);
	}
	
}

/// Get world location of linetrace through crosshair,  true if hits landscape
bool ATank_PC::GetSightRayHitLocation(FVector& locationHit) const
{
	/// Find ctosshair position
	int32 viewportSizeX, viewportSizeY;

	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);	
	//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *screenLocation.ToString());

	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *lookDirection.ToString());

		/// Line-trace along that LookDirection, and see what we hit (up to max Range)
		GetLookVectorHitLocation(lookDirection, locationHit);
	}
	
	/// Line-Trace
	return true;
}

bool ATank_PC::GetLookDirection(FVector2D screenLocation, FVector& LookDirection) const
{
	/// Screen position os crosshair to world direction
	FVector cameraWorldLocation;

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, LookDirection);
	
}

bool ATank_PC::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FHitResult hit;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			hit,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
	   )
	{
		hitLocation = hit.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false; /// Line Trace didn´t succeed
}
