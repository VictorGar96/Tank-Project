// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float rotationSpeed)
{
	rotationSpeed = FMath::Clamp<float>(rotationSpeed, -1, +1);

	auto elevationChange = rotationSpeed * degreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rotation = RelativeRotation.Yaw + elevationChange;

	SetRelativeRotation(FRotator(0, rotation, 0));
}
