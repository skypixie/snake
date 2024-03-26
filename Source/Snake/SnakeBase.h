// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
class APlayerPawnBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


UCLASS()
class SNAKE_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	APlayerPawnBase* Owner;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	// Seconds between ticks
	UPROPERTY(EditDefaultsOnly)
	float TickInterval;

	UPROPERTY()
	bool CanTurn = true;

	UPROPERTY(EditDefaultsOnly)
	int SnakeStartSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Move();

	UFUNCTION(BlueprintCallable)
	FVector TranslateXYToXYZ(FVector2D XYVector);

	UFUNCTION()
	void SetMovementDirection(FVector2D MovementVector);

	void MakeStartSnake();

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other);

	UFUNCTION(BlueprintCallable)
	void IncreaseSnakeSpeed();

	UFUNCTION(BlueprintCallable)
	void AddSnakeElement();

	UFUNCTION()
	void GameOver();
};
