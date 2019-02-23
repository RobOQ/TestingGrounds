// Copyright 2019 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Generation")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.0f);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool FindEmptyLocation(float Radius, FVector& OutLocation);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint);
	bool CanSpawnAtLocation(FVector Location, float Radius);

};
