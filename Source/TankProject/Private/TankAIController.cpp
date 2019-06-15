// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn * inPawn)
{
	Super::SetPawn(inPawn);

	if (inPawn)
	{
		auto possessedTank = Cast<ATank>(inPawn);
		if (!ensure(possessedTank)) { return; }

		/// subscribe to our local method the the tank death event
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	auto controlledTank = GetPawn();

	if (!playerTank || !controlledTank) { return; }
	
	MoveToActor(playerTank, acceptenceRadius);

	/// Aim towards the player
	auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());

	/// Fire if ready
	if (aimingComponent->GetFiringState() == EFiringState::Locked)
	{
		aimingComponent->Fire();
	}
	
}


 