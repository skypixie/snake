// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "SnakeBase.h"
#include "SpawnerBase.h"


// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorRotation(FRotator(0, -90, 0));
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PlayerEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PlayerEI->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawnBase::HandleInput);
	PlayerEI->BindAction(StartGameAction, ETriggerEvent::Triggered, this, &APlayerPawnBase::StartGame);
}

void APlayerPawnBase::HandleInput(const FInputActionValue& Value)
{
	if (Controller != nullptr && IsValid(SnakeActor))
	{
		const FVector2D MovementValue = Value.Get<FVector2D>();
		SnakeActor->SetMovementDirection(MovementValue);
	}
}

void APlayerPawnBase::StartGame()
{
	if (!IsValid(SnakeActor))
	{
		CreateSnakeActor();
		CreateSpawner();
		GetWorldTimerManager().SetTimer(SnakeDeathTimerHandle, this, &APlayerPawnBase::GameOver, SnakeLifetime, false);
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &APlayerPawnBase::ReceiveDamage, 1, true);
	}
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
	if (IsValid(SnakeActor))
	{
		SnakeActor->Owner = this;
	}
}

void APlayerPawnBase::CreateSpawner()
{
	FVector Location(0, 20, 0);
	Spawner = GetWorld()->SpawnActor<ASpawnerBase>(SpawnerActorClass, FTransform(Location));
	if (IsValid(Spawner))
	{
		Spawner->Owner = this;
	}
}

void APlayerPawnBase::IncreaseScore()
{
	Score += 10;
	ResetHealth();
}

void APlayerPawnBase::ResetHealth()
{
	SnakeHealth = 100.f;
	GetWorldTimerManager().ClearTimer(SnakeDeathTimerHandle);
	GetWorldTimerManager().SetTimer(SnakeDeathTimerHandle, this, &APlayerPawnBase::GameOver, SnakeLifetime, false);
}

void APlayerPawnBase::ReceiveDamage()
{
	SnakeHealth -= 100 / SnakeLifetime;
}

void APlayerPawnBase::GameOver_Implementation()
{
}
