// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

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
	aimingComponent->Fire(); // TODO limit firing rate and fix it
	
}

 