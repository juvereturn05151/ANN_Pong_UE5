// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the mesh component
	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = PaddleMesh;

	// Default speed
	Speed = 500.0f;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving up/down
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &APaddle::MoveUp);
		EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &APaddle::MoveDown);
	}
}

void APaddle::MoveUp(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() > 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += Speed * GetWorld()->GetDeltaSeconds();

		// Clamp Y position between -800 and 800
		NewLocation.Y = FMath::Clamp(NewLocation.Y, -800.0f, 800.0f);

		SetActorLocation(NewLocation);
	}
}

void APaddle::MoveDown(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() > 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Y -= Speed * GetWorld()->GetDeltaSeconds();

		// Clamp Y position between -800 and 800
		NewLocation.Y = FMath::Clamp(NewLocation.Y, -800.0f, 800.0f);

		SetActorLocation(NewLocation);
	}
}

