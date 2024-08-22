// Copyright Epic Games, Inc. All Rights Reserved.

#include "FallGuySurvivalGameMode.h"
#include "BaseClass/TFPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFallGuySurvivalGameMode::AFallGuySurvivalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}