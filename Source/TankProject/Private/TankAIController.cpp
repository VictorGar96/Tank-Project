// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//auto controlledTank = GetControlledTank();

	//if (controlledTank == NULL)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"));
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("Player controller possesing %s"), *(controlledTank->GetName()));


	if (GetPlayerTank() == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player IA controller not found"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Player IA controller found %s"), *(GetPlayerTank()->GetName()));
}

ATank * ATankAIController::GetControlledTank() const
{
	return  Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!playerPawn)
	{
		return NULL;
	}
	
	return Cast<ATank>(playerPawn);
}
 