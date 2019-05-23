// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	/// Move the barrel the right amout this frma
	/// given a max elevation speed adn the frame time

	/*auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f Barrel Elevate() called %f"), time,relativeSpeed);
	*/

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);


	auto elevationChange = relativeSpeed * MaxDregreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;

	auto clampElevation = FMath::Clamp<float>(rawNewElevation, MinDregreesElevation, MaxDregreesElevation);

	SetRelativeRotation(FRotator(clampElevation, 0, 0));

}


