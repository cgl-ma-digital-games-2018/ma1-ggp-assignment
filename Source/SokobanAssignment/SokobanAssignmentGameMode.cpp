// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SokobanAssignmentGameMode.h"
#include "SokobanAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "BoxGoal/BoxGoal.h"
#include "Box/MovableBox.h"

ASokobanAssignmentGameMode::ASokobanAssignmentGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

void ASokobanAssignmentGameMode::CheckForWinCondition()
{
	auto const bIsWinConditionMet = CheckAllBoxGoals();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Win condition: %s"),
		(bIsWinConditionMet ? TEXT("MET!") : TEXT("NOT MET!"))
	);

	if (bIsWinConditionMet)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Passing win condition handling to blueprint.")
		);
		// Interface to Blueprints. Implementation in Blueprint.
		HandleWinCondition();
	}
}

void ASokobanAssignmentGameMode::StartPlay()
{
	Super::StartPlay();

	BoxGoals = GetBoxGoals();
	CheckAllBoxGoals();
}

bool ASokobanAssignmentGameMode::IsOverlappingMovableBox(AActor* Actor)
{
	TArray<AActor*> OverlappingMovableBoxes;
	TSubclassOf<AMovableBox> const ClassFilter;
	Actor->GetOverlappingActors(OUT OverlappingMovableBoxes, ClassFilter);

	return (OverlappingMovableBoxes.Num() > 0);
}

bool ASokobanAssignmentGameMode::CheckAllBoxGoals()
{
	auto bAllBoxGoalsAreOverlapping = true;

	for (int i = 0; i < BoxGoals.Num(); i++)
	{
		auto const BoxGoal = BoxGoals[i];

		auto const bIsOverlappingMovableBox = IsOverlappingMovableBox(BoxGoal);

		if (!bIsOverlappingMovableBox)
		{
			bAllBoxGoalsAreOverlapping = false;
		}

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Found BoxGoal %s. Overlapping with MovableBox = %s"),
			*GetNameSafe(BoxGoal),
			(bIsOverlappingMovableBox ? TEXT("True") : TEXT("False"))
		);
	}

	return bAllBoxGoalsAreOverlapping;
}

TArray<AActor*> ASokobanAssignmentGameMode::GetBoxGoals()
{
	TArray<AActor*> Temp;

	// Finds all ABoxGoal Actors by type (needs a UWorld object).
	for (TActorIterator<ABoxGoal> It(GetWorld()); It; ++It)
	{
		Temp.Add(*It);

		CheckAllBoxGoals();
	}

	return Temp;
}