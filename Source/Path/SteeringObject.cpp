// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringObject.h"


ASteeringObject::ASteeringObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASteeringObject::BeginPlay()
{
	Super::BeginPlay();
	position = GetActorLocation();
	velocity = { -50.f,-50.f,0 };
	orientation = GetActorRotation();

}

// Called every frame
void ASteeringObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector current_strategy;
	switch (Strategy) {
	case SEEK:
		current_strategy = Seek();
		break;
	case FLEE:
		current_strategy = Flee();
		break;
	case PURSUE:
		current_strategy = Pursue();
		break;
	case EVADE:
		current_strategy = Evade();
		break;
	case CIRCUIT:
		current_strategy = Circuit();
		break;
	case ONEWAY:
		current_strategy = OneWay();
	case TWOWAY:
		current_strategy = TwoWay();
	default:
		current_strategy = Seek();
		break;
	}

	FVector steering_force = Truncate(current_strategy, max_force);
	FVector acceleration = steering_force / mass;
	velocity = Truncate(velocity + acceleration, max_speed);
	position = position + velocity;
	orientation = velocity.Rotation();
	SetActorLocation(FVector(position.X, position.Y, position.Z));
	SetActorRotation(orientation);
}


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
	if (position.Equals(CurrentCircuit[CurrentCircuit.Num()-1]->GetActorLocation(),10)) {
		WayEnd = true;
		max_speed = 0;
	}
	if (WayEnd) {
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

FVector ASteeringObject::TwoWay()
{
	if ((CurrentCircuit[CurrentCircuit.Num() - 1]->GetActorLocation() - position).Size() < 10) 
	{
		WayEnd = true;
	}
	else if ((CurrentCircuit[0]->GetActorLocation() - position).Size() < 10) 
	{
		WayEnd = false;
	}
	if ((target->GetActorLocation() - position).Size() < 10) {
		circuitIndex = WayEnd ? circuitIndex -= 1 : circuitIndex += 1;
	}
	target = CurrentCircuit[circuitIndex];
	//when arrive to the target  stop wait 2sec and go to next target 
	//if lasttaget go first target 
	return Seek();
}


