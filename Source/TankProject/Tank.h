// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	/// Called by the engine when actor gets damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser) override;

	/// Returns current health and a porcentage of tarting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPorcent();

	FTankDelegate OnDeath;

private:
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, category = "SetUp")
	int32 maxHealth = 100;

	UPROPERTY(Visibleanywhere, category = "SetUp")
	int32 currentHealth = 0;

};
