// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	mass = 1;
	position = GetActorLocation();
	velocity = GetVelocity();
	orientation = GetActorRotation();
	max_force = 100;
	max_speed = 100;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector steering_force = truncate(GetActorLocation(), max_force);
	FVector acceleration = steering_force / mass;
	velocity = truncate(velocity + acceleration, max_speed);
	position = position + velocity;
	SetActorLocation(position);
}

