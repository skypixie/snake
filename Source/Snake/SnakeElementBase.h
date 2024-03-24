// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Interactable.h"
#include "SnakeElementBase.generated.h"

class ASnakeBase;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class SNAKE_API ASnakeElementBase : public APaperSpriteActor, public IInteractable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbook* Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASnakeBase* SnakeOwner;

protected:
	UFUNCTION()
	void HandleHeadOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& HitResult);

public:
	ASnakeElementBase();
	// ----- FUNCTIONS -----

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElemType();
	void SetFirstElemType_Implementation();

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION()
	void ToggleCollision();

	UFUNCTION(BlueprintCallable)
	void UpdateFrameRate();
};
