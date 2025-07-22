// Fill out your copyright notice in the Description page of Project Settings.


#include "ANNNeuron.h"

ANNNeuron::ANNNeuron(int InNumInputs)
{
	NumInputs = InNumInputs;
	Weights.SetNum(NumInputs);
	Inputs.SetNum(NumInputs);
	for (int i = 0; i < NumInputs; ++i)
	{
		Weights[i] = FMath::FRandRange(-0.5f, 0.5f);
	}
	Bias = FMath::FRandRange(-0.5f, 0.5f);
}

ANNNeuron::ANNNeuron()
{
}

ANNNeuron::~ANNNeuron()
{
}
