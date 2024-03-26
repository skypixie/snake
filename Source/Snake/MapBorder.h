// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapBorder.generated.h"

class UBoxComponent;

UCLASS()
class SNAKE_API AMapBorder : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapBorder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

};
