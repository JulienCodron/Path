// Fill out your copyright notice in the Description page of Project Settings.


#include "npc.h"

// Called when the game starts or when spawned
Anpc::Anpc()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void Anpc::BeginPlay()
{
	Super::BeginPlay();
	position = GetActorLocation();
	velocity = { -50.f,-50.f,0 };
	orientation = GetActorRotation();
	
}

// Called every frame
void Anpc::Tick(float DeltaTime)
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
		default:
			current_strategy = Seek();
			break;
	}

	FVector steering_force = Truncate(current_strategy, max_force);
	FVector acceleration = steering_force / mass;
	velocity = Truncate(velocity + acceleration, max_speed);
	position = position + velocity;
	orientation = velocity.Rotation();
	SetActorLocation(FVector(position.X,position.Y,position.Z));
	SetActorRotation(orientation);
}
