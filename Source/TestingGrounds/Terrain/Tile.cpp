// Copyright 2019 Robert O'Quinn

#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors()
{
	FVector Min(0.0f, -2000.0f, 0.0f);
	FVector Max(4000.0f, 2000.0f, 0.0f);
	FBox Bounds(Min, Max);
	for(int i = 0; i < 20; ++i)
	{
		FVector RandPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("Random Point: %s"), *RandPoint.ToCompactString());
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

