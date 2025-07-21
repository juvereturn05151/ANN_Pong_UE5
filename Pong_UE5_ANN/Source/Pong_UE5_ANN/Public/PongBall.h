// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PongBall.generated.h"

UCLASS()
class PONG_UE5_ANN_API APongBall : public APawn
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

    UFUNCTION(BlueprintCallable)
    void OnCollidingWall();

    // Gets the current movement direction
    UFUNCTION(BlueprintPure, Category = "Ball")
    FVector GetCurrentDirection() const { return CurrentDirection; }

    // Sets a new movement direction (automatically normalized)
    UFUNCTION(BlueprintCallable, Category = "Ball")
    void SetCurrentDirection(FVector NewDirection);

private:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UFloatingPawnMovement* MovementComponent;

    // Physics
    UPROPERTY(EditDefaultsOnly, Category = "Physics")
    float InitialSpeed = 500.0f;

    UPROPERTY()
    FVector BallStartPosition = FVector::ZeroVector;

    FVector CurrentDirection;

    // Ensures 2D movement
    void ConstrainTo2DPlane();

};
