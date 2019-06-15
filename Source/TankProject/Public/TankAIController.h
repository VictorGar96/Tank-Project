// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* inPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	
	/// How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = "Setup")
	float acceptenceRadius = 3000.f;

};
