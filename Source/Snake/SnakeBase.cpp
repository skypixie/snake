// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastMoveDirection = EMovementDirection::UP;
	ElementSize = 100.f;
	SnakeStartSize = 3;
	TickInterval = 0.5f;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(TickInterval);
	
	MakeStartSnake();
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

/*
* The map is placed vertically,
* so we need a function that translates XY movement to XYZ
* considering the map placement
* for easier development
*/
FVector ASnakeBase::TranslateXYToXYZ(FVector2D XYVector)
{
	return FVector(XYVector.X, 5, XYVector.Y);
}

void ASnakeBase::SetMovementDirection(FVector2D MovementVector)
{
	if (MovementVector.X)
	{
		int MoveVal = MovementVector.X;
		switch (MoveVal)
		{
		case 1:
			LastMoveDirection = EMovementDirection::RIGHT;
			break;
		case -1:
			LastMoveDirection = EMovementDirection::LEFT;
			break;
		}
	}
	else
	{
		int MoveVal = MovementVector.Y;
		switch (MoveVal)
		{
		case 1:
			LastMoveDirection = EMovementDirection::UP;
			break;
		case -1:
			LastMoveDirection = EMovementDirection::DOWN;
			break;
		}
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(FVector::ZeroVector);

	switch (LastMoveDirection) {
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y -= ElementSize;
		break;
	}

	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		
	}
}

void ASnakeBase::MakeStartSnake()
{
	for (int i = 0; i < SnakeStartSize; ++i)
	{
		FVector2D NewLocation2D(0, SnakeElements.Num() * -ElementSize);
		FVector NewLocation(TranslateXYToXYZ(NewLocation2D));
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);

		if (NewSnakeElem)
		{
			NewSnakeElem->SnakeOwner = this;
			int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
			if (ElemIndex == 0)
			{
				NewSnakeElem->SetFirstElemType();
			}
		}
	}
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other)
{

}
