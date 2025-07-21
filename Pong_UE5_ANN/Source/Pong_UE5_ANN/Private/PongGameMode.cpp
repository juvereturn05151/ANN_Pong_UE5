// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "PongBall.h"
APongGameMode::APongGameMode()
{

}

void APongGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Option 1: Automatically find and set the first camera in the level
    TArray<AActor*> Cameras;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);

    if (Cameras.Num() > 0)
    {
        MainCamera = Cast<ACameraActor>(Cameras[0]);
        SetMainCamera(MainCamera);

        // Spawn ball after camera is set
        SpawnGameBall();
    }
}

void APongGameMode::SetMainCamera(ACameraActor* NewCamera)
{
    if (!NewCamera) return;

    MainCamera = NewCamera;
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

    if (PC)
    {
        PC->SetViewTargetWithBlend(MainCamera, 0.5f); // Smooth blend
    }
}

void APongGameMode::SpawnGameBall()
{
    if (!BallClass) return;
    if (!MainCamera) return;

    // Get camera's center position in world space
    FVector CameraLocation = MainCamera->GetActorLocation();
    FRotator CameraRotation = MainCamera->GetActorRotation();
    FVector SpawnLocation = CameraLocation;// +CameraRotation.Vector() * 500.0f; // Adjust distance as needed

    // Spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Spawn the ball
    APongBall* Ball = GetWorld()->SpawnActor<APongBall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

    // Optional: Adjust for 2D (set Z to 0)
    if (Ball)
    {
        FVector NewLocation = Ball->GetActorLocation();
        NewLocation.Z = 0.0f;
        Ball->SetActorLocation(NewLocation);
    }
}
