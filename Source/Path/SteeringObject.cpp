// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringObject.h"


FVector ASteeringObject::Truncate(FVector v, const float& max)
{
	if (v.Size() > max)
	{
		return v.GetSafeNormal() * max;
	}
	return v;
}

FVector ASteeringObject::Seek()
{
	FVector direction = (target->GetActorLocation() - position).GetSafeNormal();
	FVector desired_velocity = direction * max_speed;
	return desired_velocity - velocity;
}

FVector ASteeringObject::Flee()
{
	FVector direction = -Seek();
	return FVector(direction.X, direction.Y, 0);
}

FVector ASteeringObject::Pursue()
{
	float distance = (target->GetActorLocation() - position).Size();
	float T = distance * TurningParameter;
	FVector tagetVelocity = target->GetVelocity();
	if (tagetVelocity.IsNearlyZero()) {
		return Seek();
	}

	FVector FuturTarget = target->GetVelocity() * T;
	FVector direction = FuturTarget + target->GetActorLocation();
	return FVector(direction.X,direction.Y,0);
}

FVector ASteeringObject::Evade()
{
	//add random zigzag ( si distance < x tourner
	float distance = -(target->GetActorLocation() - position).Size();
	float T = distance * TurningParameter;
	FVector tagetVelocity = target->GetVelocity();
	if (tagetVelocity.IsNearlyZero()) {
		return Flee();
	}

	FVector FuturTarget = -target->GetVelocity() * T;
	FVector direction = FuturTarget;
	return FVector(direction.X, direction.Y, 0);
}

FVector ASteeringObject::Circuit()
{
	if ((target->GetActorLocation() - position).Size() < 10) {
		if (circuitIndex == CurrentCircuit.Num()-1) {
			circuitIndex = 0;
		}
		else
		{
			circuitIndex += 1;
		}
	}
	target = CurrentCircuit[circuitIndex];
	//when arrive to the target  stop wait 2sec and go to next target 
	//if lasttaget go first target 
	return Seek();
}


