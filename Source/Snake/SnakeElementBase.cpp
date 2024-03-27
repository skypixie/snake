// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"
#include "SnakeBase.h"

ASnakeElementBase::ASnakeElementBase()
{
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionMesh->SetupAttachment(GetRootComponent());

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Sprite->SetupAttachment(CollisionMesh);

	if (Sprite)
	{
		Sprite->SetFlipbook(Anim);
	}
}

void ASnakeElementBase::SetFirstElemType_Implementation()
{
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleHeadOverlap);
}

void ASnakeElementBase::HandleHeadOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& HitResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, TEXT("SnakeBase interact"));
		Snake->GameOver();
	}
}

void ASnakeElementBase::ToggleCollision()
{
	if (CollisionMesh->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASnakeElementBase::UpdateFrameRate()
{
	Sprite->SetPlayRate((SnakeOwner->TickInterval) / (Sprite->GetFlipbookLengthInFrames()) * 2);
}
