// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PC.h"



void ATank_PC::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (controlledTank == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Player controller possesing %s"), *(controlledTank->GetName()));


}

ATank* ATank_PC::GetControlledTank() const
{
	/// Returns the player controller posseed
	return Cast<ATank>(GetPawn());
}
