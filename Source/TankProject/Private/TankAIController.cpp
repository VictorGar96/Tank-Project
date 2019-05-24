// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	auto controlledTank = Cast<ATank>(GetPawn());

	if (playerTank)
	{
		/// Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		/// Fire if ready
		controlledTank->Fire(); // TODO limit firing rate
	}
}

 