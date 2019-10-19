// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "TextureResource.h"
#include "GameFramework/Character.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Element : ColorToAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Color to asset mapping found: COLOR (key): %s ASSET (value): %s"), *Element.Key.ToString(), *Element.Value->GetName());
	}

	GenerateLevel();
}

void ALevelGenerator::GenerateLevel() const
{
	ensureMsgf(LevelTexture != nullptr, TEXT("No LevelTexture has been found."));

	// The MipMap 0 (original resolution) of the Texture2D used for level creation.
	FTexture2DMipMap* LevelTextureMipMap = &LevelTexture.LoadSynchronous()->PlatformData->Mips[0];

	// The raw image data.
	FByteBulkData* RawImageData = &LevelTextureMipMap->BulkData;

	// Locks the texture data, in case it is used in the rendering thread.
	FColor* FormattedImageData = static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));

	auto const TextureWidth = LevelTextureMipMap->SizeX;
	auto const TextureHeight = LevelTextureMipMap->SizeY;

	for (int32 x = 0; x < TextureWidth; x++)
	{
		for (int32 y = 0; y < TextureHeight; y++)
		{
			FColor PixelColor = FormattedImageData[y * TextureWidth + x];

			if (PixelColor != PixelColor.Transparent)
			{
				UE_LOG(LogTemp, Warning, TEXT("Texture pixel values at X = %d Y = %d: %s"), x, y, *PixelColor.ToString());

				InstantiateAssetFromPixel(PixelColor, x, y);
			}
		}
	}

	RawImageData->Unlock();
}

void ALevelGenerator::InstantiateAssetFromPixel(FColor PixelColor, int32 PixelX, int32 PixelY) const
{
	auto const ActorFromColor = ColorToAsset.FindRef(PixelColor).Get();

	if (ActorFromColor != nullptr)
	{
		int32 const WorldX = (PixelY - 10) * 100 * -1;
		int32 const WorldY = PixelX * 100;

		// Moves player according to level image, if defined.
		if (ActorFromColor->IsChildOf(APlayerStart::StaticClass()))
		{
			// Finds all APlayerStart Actors by type (needs a UWorld object).
			for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
			{
				auto const PlayerCharacter = *It;
				PlayerCharacter->SetActorLocation(FVector(WorldX, WorldY, 500));

				UE_LOG(LogTemp, Warning, TEXT("Player moved according to pixel coordinates."));
			}

			return;
		}

		auto SpawnLocation = new FVector(WorldX, WorldY, 0);
		FActorSpawnParameters SpawnParameters;

		GetWorld()->SpawnActor<AActor>(ActorFromColor, *SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
		UE_LOG(LogTemp, Warning, TEXT("Instantiated %s at %s."), *ActorFromColor->GetName(), *SpawnLocation->ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ActorFromColor is nullptr."));
	}
}