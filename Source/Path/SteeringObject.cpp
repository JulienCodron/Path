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
	return -Seek();
}

FVector ASteeringObject::Pursue()
{
	float distance = (target->GetActorLocation() - position).Size();
	float T = distance * TurningParameter;
	FVector FuturTarget = target->GetVelocity() * T;
	return FuturTarget + target->GetActorLocation();
}

FVector ASteeringObject::Evade()
{
	//add random zigzag ( si distance < x tourner
	return -Pursue();
}
