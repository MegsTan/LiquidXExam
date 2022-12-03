// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExamGameMode.h"
#include "ExamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExamGameMode::AExamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
