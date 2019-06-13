// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Gameframework/Actor.h"
#include "GameFramework/PlayerController.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	/// Set default simulate physics to "true"
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float launchSpeed)
{
	/// Allow to get the worlds time reference in seconds
	auto time = GetWorld()->GetTimeSeconds();

	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank fires"), time);

	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * launchSpeed);
	projectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	launchBlast->Deactivate();
	impactBlast->Activate();
}

