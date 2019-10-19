// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class SOKOBANASSIGNMENT_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/// --- Variables

	// The Texture2D to read pixel values for level creation from.
	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UTexture2D> LevelTexture;

	// The static mesh blueprint used when spawning a wall section.
	/*UPROPERTY(EditAnywhere, Category = "Asset Blueprints")
		TSubclassOf<class AStaticMeshActor> WallSection = nullptr;*/

		// The association of a color value to an asset to be spawned.
	UPROPERTY(EditAnywhere)
		TMap <FColor, TSubclassOf<AActor>> ColorToAsset;

	/// --- Functions

	// Generates the level from Texture2D data.
	void GenerateLevel() const;

	void InstantiateAssetFromPixel(FColor PixelColor, int32 PixelX, int32 PixelY) const;
};
