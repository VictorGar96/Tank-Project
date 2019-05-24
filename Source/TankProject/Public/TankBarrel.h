// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) // hidecategories("Collision")
class TANKPROJECT_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	/// -1 max downward speed
	///  1 max up movement 
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category= Setup)
	float MaxDregreesPerSecond = 5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDregreesElevation = 40;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDregreesElevation = 0;

};
