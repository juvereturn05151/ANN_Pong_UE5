// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>

/**
 * 
 */
class PONG_UE5_ANN_API ANNNeuron
{
public:
	int NumInputs;
	TArray<double> Weights;
	TArray<double> Inputs;
	double Output = 0.0;
	double Bias = 0.0;
	double ErrorGradient = 0.0;

	ANNNeuron(int InNumInputs);
	ANNNeuron();
	~ANNNeuron();
};
