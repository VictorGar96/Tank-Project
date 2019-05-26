// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	//auto tankName = GetOwner()->GetName();

	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = moveVelocity.GetSafeNormal();

	/// Returns a float
	auto forwardThrow = FVector::DotProduct(tankForward, AIForwardIntention);
	IntendMoveForward(forwardThrow);

	/// Returns a Vector
	auto rightTrowh = FVector::CrossProduct(tankForward, AIForwardIntention).Z;
	IntendTurnRight(rightTrowh);

	UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), rightTrowh, forwardThrow);

}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), _throw);

	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(_throw);
	rightTrack->SetThrottle(_throw);

}
void UTankMovementComponent::IntendTurnRight(float _throw)
{
	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(_throw);
	rightTrack->SetThrottle(-_throw);
}





