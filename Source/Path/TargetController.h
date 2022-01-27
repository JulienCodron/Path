// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TargetController.generated.h"

/**
 * 
 */
UCLASS()
class PATH_API ATargetController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
