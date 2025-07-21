// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
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