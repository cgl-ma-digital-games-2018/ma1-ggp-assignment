// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxGoal.h"
#include "Engine/World.h"

// Sets default values
ABoxGoal::ABoxGoal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoxGoal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoxGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}