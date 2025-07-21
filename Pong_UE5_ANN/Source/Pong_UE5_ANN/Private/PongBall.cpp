// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

APongBall::APongBall()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create mesh component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    // Setup collision (no physics needed)
    BallMesh->SetCollisionProfileName(FName("BlockAllDynamic"));
    BallMesh->SetEnableGravity(false);
    BallMesh->SetSimulatePhysics(false);

    // Create movement component
    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    MovementComponent->UpdatedComponent = RootComponent;
    MovementComponent->MaxSpeed = InitialSpeed;
}

void APongBall::BeginPlay()
{
    Super::BeginPlay();
    ResetBall();
}

void APongBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ConstrainTo2DPlane();

    FVector NewLocation = GetActorLocation() + CurrentDirection * InitialSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}

void APongBall::ResetBall()
{
    // Reset position
    SetActorLocation(FVector::ZeroVector);

    OnCollidingWall();
}

void APongBall::OnCollidingWall()
{   
    // Set random direction (biased toward left/right)
    CurrentDirection = FVector(
        FMath::RandBool() ? 1.0f : -1.0f, // Strong horizontal bias
        FMath::FRandRange(-0.3f, 0.3f),    // Slight vertical variation
        0.0f
    ).GetSafeNormal();

    // Apply initial velocity
    MovementComponent->Velocity = CurrentDirection * InitialSpeed;
}

void APongBall::ConstrainTo2DPlane()
{
    // Force Z-position to 0
    FVector Location = GetActorLocation();
    if (!FMath::IsNearlyZero(Location.Z))
    {
        Location.Z = 0.0f;
        SetActorLocation(Location, false, nullptr, ETeleportType::ResetPhysics);
    }
}

void APongBall::SetCurrentDirection(FVector NewDirection)
{
    // Normalize the direction and ensure it's valid
    NewDirection.Z = 0.0f; // Keep it 2D
    if (NewDirection.SizeSquared() > 0.0f)
    {
        CurrentDirection = NewDirection.GetSafeNormal();
        MovementComponent->Velocity = CurrentDirection * MovementComponent->GetMaxSpeed();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set invalid direction for PongBall"));
    }
}