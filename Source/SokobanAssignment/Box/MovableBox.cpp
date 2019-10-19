// Fill out your copyright notice in the Description page of Project Settings.

#include "MovableBox.h"

// Sets default values
AMovableBox::AMovableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovableBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

