// Fill out your copyright notice in the Description page of Project Settings.


#include "Brain.h"
#include "ANN.h"

// Sets default values
ABrain::ABrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrain::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<double> ABrain::Run(double Bx, double By, double BVx, double BVy, double Px, double Py, double Pv, bool bTrain)
{
	TArray<double> Inputs = { Bx, By, BVx, BVy, Px, Py };
	TArray<double> Desired = { Pv };

	return bTrain ? NeuralNet.Train(Inputs, Desired) : NeuralNet.CalcOutput(Inputs);
}

// Called every frame
void ABrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

