// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine.h"
#include "Components/ActorComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
 
void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	AppluSideWayForce();
	currentThrottle = 0;
}

void UTankTrack::AppluSideWayForce()
{
	/// Obtenemos el detaTime del mundo
	auto deltaTime = GetWorld()->GetDeltaSeconds();

	/// Corrección del movimiento lateral. Evitando el deslizacimiento al rotar el tanque
	/// --------------------------------------------------------------------------------------------------------

	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();

	/// Accedemos al padre en este caso es un SceneComponent, necesitamos staticMesh por eso hacemos el cast
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	/// Calculamos la fuerza que hay que añadir y se la aplicamos a los lados
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; /// 1 por track
	tankRoot->AddForce(correctionForce);
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"));

	/// --------------------------------------------------------------------------------------------------------
}


void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingforce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}






