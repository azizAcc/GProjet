// Copyright Epic Games, Inc. All Rights Reserved.

#include "KageBunshinGameMode.h"
#include "KageBunshinCharacter.h"

AKageBunshinGameMode::AKageBunshinGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AKageBunshinCharacter::StaticClass();	
}
