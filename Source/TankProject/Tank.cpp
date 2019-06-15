// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	/// Redondea la variable
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0)
	{
		OnDeath.Broadcast(); 
	}

	return damageToApply;
}

float ATank::GetHealthPorcent()
{
	return (float)currentHealth / (float)maxHealth;
}


