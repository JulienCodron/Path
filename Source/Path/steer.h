// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PATH_API steer
{
public:
	steer();
	~steer();

	FVector truncate(FVector v, const float& max);
	FRotator calculateDirection();
	FVector seek(const FVector target);
	FVector flee(const FVector target);
	FVector pursue(const FVector target);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPhysic", meta = (AllowPrivateAccess = "true"))
		float mass = 1;

	FVector position;
	FVector velocity;
	FRotator orientation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPhysic", meta = (AllowPrivateAccess = "true"))
		float max_force = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPhysic", meta = (AllowPrivateAccess = "true"))
		float max_speed = 100;
};
