// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBase.generated.h"

class UBoxComponent;
class APlayerPawnBase;
class AFood;

/*
* Class for spawning food and obstacles
*/
UCLASS()
class SNAKE_API ASpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerBase();

	APlayerPawnBase* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionMesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;


	/* True if spawner can spawn items, false otherwise */
	bool bCanSpawn;

	/* Handles the delay between spawns */
	FTimerHandle SpawnDelayTimerHandle;

	/* Rests the spawners ability to spawn items */
	void ResetSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnItem();

};
