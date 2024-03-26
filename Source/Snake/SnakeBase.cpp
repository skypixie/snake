// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "PlayerPawnBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastMoveDirection = EMovementDirection::UP;
	ElementSize = 100.f;
	SnakeStartSize = 3;
	TickInterval = 0.35f;
	CanTurn = true;
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
	return FVector(XYVector.X, 0, XYVector.Y);
}

void ASnakeBase::SetMovementDirection(FVector2D MovementVector)
{
	// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%f %f"), MovementVector.X, MovementVector.Y));
	if (MovementVector.X)
	{
		if (
			LastMoveDirection == EMovementDirection::LEFT
			|| LastMoveDirection == EMovementDirection::RIGHT
			|| !CanTurn
			) return;

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
		CanTurn = false;
	}

	if (MovementVector.Y)
	{
		if (
			LastMoveDirection == EMovementDirection::UP
			|| LastMoveDirection == EMovementDirection::DOWN
			|| !CanTurn
			) return;

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
		CanTurn = false;
	}
}

void ASnakeBase::Move()
{
	FVector2D MovementVector2D(FVector2D::ZeroVector);

	switch (LastMoveDirection) {
	case EMovementDirection::RIGHT:
		MovementVector2D.X += ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector2D.X -= ElementSize;
		break;
	case EMovementDirection::UP:
		MovementVector2D.Y += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector2D.Y -= ElementSize;
		break;
	}
	FVector MovementVector = TranslateXYToXYZ(MovementVector2D);

	SnakeElements[0]->ToggleCollision();
	// Move the body
	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];

		FVector NewLocation = PrevElement->GetActorLocation();
		CurElement->SetActorLocation(NewLocation);

		if (!CurElement->Sprite->GetVisibleFlag())
		{
			CurElement->Sprite->SetVisibility(true);
			PrevElement->Sprite->SetVisibility(true);
		}
	}
	// Move the head
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	CanTurn = true;
	SnakeElements[0]->ToggleCollision();
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
			NewSnakeElem->UpdateFrameRate();
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
	// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, TEXT("Overlap"));

	if (IsValid(OverlappedBlock))
	{
		int32 ElemIndex = 0;
		if (SnakeElements.Find(OverlappedBlock, ElemIndex))
		{
			bool bIsFirst = ElemIndex == 0;
			IInteractable* InteractableInterface = Cast<IInteractable>(Other);

			// can't use IsValid cuz interface is not an actor so just check if pointer is not null
			if (InteractableInterface && bIsFirst)
			{
				InteractableInterface->Interact(this, bIsFirst);
			}
		}
	}
}

void ASnakeBase::IncreaseSnakeSpeed()
{
	SetActorTickInterval(GetActorTickInterval() / 1.1f);
	for (auto SnakeElement : SnakeElements)
	{
		SnakeElement->UpdateFrameRate();
	}
}

// Adds element AND increases score AND sets health to 100
void ASnakeBase::AddSnakeElement()
{
	FVector LastElemLocation = SnakeElements[SnakeElements.Num() - 1]->GetActorLocation();
	FVector NewLocation = {LastElemLocation.X, 2, LastElemLocation.Z};
	FTransform NewTransform(NewLocation);
	ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
	if (NewSnakeElem)
	{
		NewSnakeElem->SnakeOwner = this;
		NewSnakeElem->UpdateFrameRate();
		NewSnakeElem->Sprite->SetVisibility(false);
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		Owner->IncreaseScore();
	}
}

// just calls owners GameOver function
void ASnakeBase::GameOver()
{
	if (IsValid(Owner))
	{
		Owner->GameOver();
	}
}
