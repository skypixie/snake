// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"
#include "SnakeBase.h"

ASnakeElementBase::ASnakeElementBase()
{
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Sprite->SetupAttachment(GetRootComponent());
	if (Sprite)
	{
		Sprite->SetFlipbook(Anim);
	}
}

void ASnakeElementBase::SetFirstElemType_Implementation()
{
	
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}

}
