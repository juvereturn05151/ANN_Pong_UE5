// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ANNNeuron.h"
/**
 * 
 */
class PONG_UE5_ANN_API ANNLayer
{
public:
	int NumNeurons;
	TArray<ANNNeuron> Neurons;

	ANNLayer(int InNumNeurons, int InputsPerNeuron);
	ANNLayer();
	~ANNLayer();
};
