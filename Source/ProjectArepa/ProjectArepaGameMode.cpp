// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ProjectArepa.h"
#include "ProjectArepaGameMode.h"
#include "ProjectArepaPawn.h"

AProjectArepaGameMode::AProjectArepaGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AProjectArepaPawn::StaticClass();
}

