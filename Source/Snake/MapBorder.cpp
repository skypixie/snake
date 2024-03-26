// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBorder.h"

#include "SnakeBase.h"

#include "Components/BoxComponent.h"


// Sets default values
AMapBorder::AMapBorder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMapBorder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapBorder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapBorder::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->GameOver();
		}
	}
}

