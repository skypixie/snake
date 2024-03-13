// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "SnakeElementBase.generated.h"

class UPaperFlipbookComponent;
class UPaperFlipbook;
class ASnakeBase;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class SNAKE_API ASnakeElementBase : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	ASnakeElementBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbook* Anim;

	UPROPERTY(EditAnywhere)
	ASnakeBase* SnakeOwner;

public:
	// ----- FUNCTIONS -----

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElemType();
	void SetFirstElemType_Implementation();

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep);

};
