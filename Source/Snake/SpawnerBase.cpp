// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerBase.h"

#include "Food.h"

#include "Components/BoxComponent.h"


// Sets default values
ASpawnerBase::ASpawnerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionMesh->SetupAttachment(GetRootComponent());

	bCanSpawn = true;
}

void ASpawnerBase::ResetSpawn()
{
	bCanSpawn = true;
	GetWorldTimerManager().ClearTimer(SpawnDelayTimerHandle);
}

// Called when the game starts or when spawned
void ASpawnerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnItem();
}

void ASpawnerBase::SpawnItem()
{
	if (bCanSpawn)
	{
		bCanSpawn = false;

		if (IsValid(FoodClass))
		{
			FVector SpawnLocation = FMath::RandPointInBox(CollisionMesh->GetNavigationBounds());
			FTransform SpawnTransform(SpawnLocation);
			GetWorld()->SpawnActor<AFood>(FoodClass, SpawnTransform);
		}

		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ASpawnerBase::ResetSpawn, 4.0f, false);
	}
}

