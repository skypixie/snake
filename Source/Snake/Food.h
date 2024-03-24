// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Food.generated.h"

class UBoxComponent;

/**
 * Adds 1 element to snake
 */
UCLASS()
class SNAKE_API AFood : public APaperSpriteActor, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbook* Anim;

public:
	AFood();
	/* ----- FUNCTIONS ----- */

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
