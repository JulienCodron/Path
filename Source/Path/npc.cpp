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
	FVector steering_force = Truncate(Seek(), max_force);
	FVector acceleration = steering_force / mass;
	velocity = Truncate(velocity + acceleration, max_speed);
	position = position + velocity;
	orientation = velocity.Rotation();
	SetActorLocation(FVector(position.X,position.Y,position.Z));
	SetActorRotation(orientation);
}
