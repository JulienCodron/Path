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
	return direction * max_speed - velocity;
}

FVector ASteeringObject::Flee()
{
	FVector direction = -Seek();
	return FVector(direction.X, direction.Y, -direction.Z);
}

FVector ASteeringObject::Pursue()
{
	float distance = (target->GetActorLocation() - position).Size();
	float dot = FVector::DotProduct(target->GetVelocity().GetSafeNormal(), (position - target->GetActorLocation()).GetSafeNormal());
	float turningParameter = 1-dot;
	float T = distance / velocity.Size();
	if (dot >= 0) {
		T = distance / velocity.Size() * turningParameter;
	}

	FVector targetVelocity = target->GetVelocity();

	if (targetVelocity.IsNearlyZero()) {
		return Seek();
	}

	FVector FuturTarget = target->GetActorLocation() + target->GetVelocity() * T / 100;
	FVector desired_velocity = (FuturTarget - position) * max_speed - velocity;
	return desired_velocity;
}

FVector ASteeringObject::Evade()
{
	FVector direction =  -Pursue();
	return FVector(direction.X, direction.Y, -direction.Z);

	//add random zigzag ( si distance < x tourner)
	//float distance = -(target->GetActorLocation() - position).Size();
	//float T = distance / velocity.Size();
	//FVector targetVelocity = target->GetVelocity();

	//if (targetVelocity.IsNearlyZero()) {
	//	return Flee();
	//}

	////FVector FuturTarget = -target->GetVelocity() * T;
	////FVector direction = FuturTarget;
	////return FVector(direction.X, direction.Y, 0);

	//FVector FuturTarget = -(target->GetActorLocation() + target->GetVelocity() * T / 100);
	//FVector desired_velocity = (FuturTarget-position) * max_speed - velocity;
	//return desired_velocity;
}

FVector ASteeringObject::Circuit()
{
	if ((target->GetActorLocation() - position).Size() < 10) {
		if (circuitIndex == CurrentCircuit.Num() - 1) {
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

FVector ASteeringObject::OneWay()
{	
	if (circuitIndex == CurrentCircuit.Num() - 1) {
		return position;
	}
	if ((target->GetActorLocation() - position).Size() < 10) {
		circuitIndex += 1;
	}
	target = CurrentCircuit[circuitIndex];
	//when arrive to the target  stop wait 2sec and go to next target 
	//if lasttaget go first target 
	return Seek();
}


