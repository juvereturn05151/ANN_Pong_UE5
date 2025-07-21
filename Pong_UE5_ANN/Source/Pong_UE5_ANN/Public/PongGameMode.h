// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
class ACameraActor;
class APongBall;
UCLASS()
class PONG_UE5_ANN_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    APongGameMode();

protected:
    virtual void BeginPlay() override;

    // Optional: Expose camera assignment to Blueprints
    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SetMainCamera(ACameraActor* NewCamera);

    // Ball spawning
    void SpawnGameBall();

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    TSubclassOf<APongBall> BallClass; // Assign this in Blueprint
private:
    UPROPERTY()
    ACameraActor* MainCamera;
};
