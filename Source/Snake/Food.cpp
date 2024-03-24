// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

#include "SnakeBase.h"

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"

AFood::AFood()
{
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionMesh->SetupAttachment(GetRootComponent());

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Sprite->SetupAttachment(CollisionMesh);

	if (Sprite)
	{
		Sprite->SetFlipbook(Anim);
	}
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement();
			this->Destroy();
		}
	}
}
