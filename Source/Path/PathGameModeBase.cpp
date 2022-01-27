// Copyright Epic Games, Inc. All Rights Reserved.


#include "PathGameModeBase.h"
#include "Target.h"
#include "UObject/ConstructorHelpers.h"
APathGameModeBase::APathGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/BP_Target"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
