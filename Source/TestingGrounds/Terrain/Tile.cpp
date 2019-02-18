// Copyright 2019 Robert O'Quinn

#include "Tile.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min(0.0f, -2000.0f, 0.0f);
	FVector Max(4000.0f, 2000.0f, 0.0f);
	FBox Bounds(Min, Max);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	UWorld* const World = GetWorld();
	for(int i = 0; i < NumberToSpawn; ++i)
	{
		FVector RandPoint = FMath::RandPointInBox(Bounds);
		FRotator SpawnRotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		AActor* Spawned = World->SpawnActor<AActor>(ToSpawn, RandPoint, SpawnRotation);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

