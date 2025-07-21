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

    // Set up physics
    BallMesh->SetSimulatePhysics(true);
    BallMesh->SetEnableGravity(false);
    BallMesh->SetConstraintMode(EDOFMode::XYPlane); // Lock to 2D plane
    BallMesh->SetLinearDamping(0.0f); // No speed reduction over time
    BallMesh->SetAngularDamping(0.1f); // Small rotation damping

    // Enable collisions
    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BallMesh->SetCollisionProfileName(FName("PhysicsActor"));
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
}

void APongBall::ResetBall()
{
    // Reset position and velocity
    SetActorLocation(FVector::ZeroVector);
    BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

    // Apply new impulse after short delay
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            // Random direction (left/right with slight vertical variation)
            float DirectionX = FMath::RandBool() ? 1.0f : -1.0f;
            float DirectionY = FMath::FRandRange(-0.3f, 0.3f);

            FVector Impulse = FVector(DirectionX * InitialSpeed, DirectionY * InitialSpeed, 0.0f);
            BallMesh->AddImpulse(Impulse, NAME_None, true);
        }, 1.0f, false); // 1 second delay
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