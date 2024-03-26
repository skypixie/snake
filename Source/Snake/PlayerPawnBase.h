// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeBase;
class UInputAction;
class ASpawnerBase;

UCLASS()
class SNAKE_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeBase> SnakeActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASpawnerBase> SpawnerActorClass;

	UPROPERTY()
	ASpawnerBase* Spawner;

	UPROPERTY(BlueprintReadWrite)
	float SnakeHealth = 100.f;

	UPROPERTY(BlueprintReadWrite)
	int Score = 0;

	FTimerHandle SnakeDeathTimerHandle;

	int SnakeLifetime = 8;

	FTimerHandle DamageTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* StartGameAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void CreateSnakeActor();

	UFUNCTION(BlueprintCallable)
	void HandleInput(const FInputActionValue& Value);

	UFUNCTION()
	void CreateSpawner();

	// Basically, it just spawns snake and spawner
	UFUNCTION()
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void IncreaseScore();

	UFUNCTION(BlueprintCallable)
	void ResetHealth();

	UFUNCTION(BlueprintCallable)
	void ReceiveDamage();

	UFUNCTION(BlueprintNativeEvent)
	void GameOver();
	void GameOver_Implementation();
};
