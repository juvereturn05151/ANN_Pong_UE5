// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ANN.h"
#include "Brain.generated.h"

class APaddle;
class APongBall;

UCLASS()
class PONG_UE5_ANN_API ABrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHuman = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BackwallTag = "BackWall";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float YVel = 0.0f;
	float PaddleMaxSpeed = 15.0f;
	float NumSaved = 0;
	float NumMissed = 0;
	FVector2D BallVelocity;

	ANN NeuralNet;

private:
	TArray<double> Run(double Bx, double By, double BVx, double BVy, double Px, double Py, double Pv, bool bTrain);
};
