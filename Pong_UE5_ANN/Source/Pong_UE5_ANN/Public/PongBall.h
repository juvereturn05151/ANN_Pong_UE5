// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

UCLASS()
class PONG_UE5_ANN_API APongBall : public AActor
{
    GENERATED_BODY()

public:
    APongBall();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Resets the ball to center with random impulse
    UFUNCTION(BlueprintCallable)
    void ResetBall();

private:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BallMesh;

    // Physics
    UPROPERTY(EditDefaultsOnly, Category = "Physics")
    float InitialSpeed = 500.0f;

    // Ensures 2D movement
    void ConstrainTo2DPlane();

};
