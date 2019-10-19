// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SokobanAssignmentGameMode.generated.h"

UCLASS(minimalapi)
class ASokobanAssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor.
	ASokobanAssignmentGameMode();

	// Checks if the win condition has been met.
	UFUNCTION(BlueprintCallable)
		void CheckForWinCondition();

	// Handles what happens after the win condition has been met.
	// Implementation in Blueprint.
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
		void HandleWinCondition();

private:
	/// --- Variables.

	// The BoxGoals in the current map.
	TArray<AActor*> BoxGoals;

	/// --- Functions.

	virtual void StartPlay() override;

	// Checks if a single Actor is overlapping with a movable box.
	bool IsOverlappingMovableBox(AActor* Actor);

	// Checks all BoxGoals for overlaps with a movable box.
	bool CheckAllBoxGoals();

	// Gets the BoxGoals in the map.
	TArray<AActor*> GetBoxGoals();
};
