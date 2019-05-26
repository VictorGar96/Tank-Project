// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank_PC.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class TANKPROJECT_API ATank_PC : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	
	UFUNCTION(BlueprintImplementableEvent, category = "Setup")
	void foundAimingComponent(UTankAimingComponent* aimCompRef);

private:

	UPROPERTY(EditAnywhere)
	float crossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float crossHairYLocation = 0.3333f;

	UPROPERTY(EditAnyWhere)
	float lineTraceRange = 1000000;

	/// Start the tank moving the barrel so that a shot would 
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& locationHit) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

};
