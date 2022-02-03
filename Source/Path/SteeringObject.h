// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteeringObject.generated.h"


UENUM()
enum PathingStrategy {
	SEEK UMETA(DisplayName = "Seek"),
	FLEE UMETA(DisplayName = "Flee"),
	PURSUE UMETA(DisplayName = "Pursue"),
	EVADE UMETA(DisplayName = "Evade"),
	CIRCUIT UMETA(DisplayName = "Circuit"),
	ONEWAY UMETA(DisplayName = "OneWay")
};


UCLASS()
class PATH_API ASteeringObject : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		float mass = 10.f;

	FVector position;
	FVector velocity;
	FRotator orientation;
	int circuitIndex = 0;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		float max_force = 1.f;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		float max_speed = 10.f;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		AActor *target;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		float TurningParameter;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<PathingStrategy> Strategy;

	UPROPERTY(EditAnywhere, Category = "SteeringParam", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> CurrentCircuit;

public:
	FVector Truncate(FVector v, const float& max);
	FVector Seek();
	FVector Flee();
	FVector Pursue();
	FVector Evade();
	FVector Circuit();
	FVector OneWay();
};



