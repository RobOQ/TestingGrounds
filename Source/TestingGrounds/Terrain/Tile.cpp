// Copyright 2019 Robert O'Quinn

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for(int i = 0; i < NumberToSpawn; ++i)
	{
		FVector SpawnPoint;
		bool FoundLocation = FindEmptyLocation(Radius, SpawnPoint);
		if(FoundLocation)
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
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

void ATile::Destroyed()
{
	Super::Destroyed();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for(int i = 0; i < AttachedActors.Num(); ++i)
	{
		AttachedActors[i]->Destroy();
	}
}

bool ATile::FindEmptyLocation(float Radius, FVector& OutLocation)
{
	FVector Min(0.0f, -2000.0f, 0.0f);
	FVector Max(4000.0f, 2000.0f, 0.0f);
	FBox Bounds(Min, Max);

	const int MAX_ATTEMPTS = 5;

	for(int i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if(CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}
	
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	DrawDebugSphere(
		GetWorld(),
		GlobalLocation,
		Radius,
		16,
		ResultColor,
		true,
		100.0f
	);

	return !HasHit;
}
