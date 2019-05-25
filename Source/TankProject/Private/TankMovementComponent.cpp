// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) { return; }

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), _throw);

	leftTrack->SetThrottle(_throw);
	rightTrack->SetThrottle(_throw);

}
void UTankMovementComponent::IntendTurnRight(float _throw)
{
	leftTrack->SetThrottle(_throw);
	rightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnLeft(float _throw)
{
	leftTrack->SetThrottle(_throw);
	rightTrack->SetThrottle(-_throw);
}

