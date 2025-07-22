// Fill out your copyright notice in the Description page of Project Settings.


#include "ANNLayer.h"

ANNLayer::ANNLayer(int InNumNeurons, int InputsPerNeuron)
{
	NumNeurons = InNumNeurons;
	for (int i = 0; i < NumNeurons; ++i)
	{
		Neurons.Add(ANNNeuron(InputsPerNeuron));
	}
}

ANNLayer::ANNLayer()
{
}

ANNLayer::~ANNLayer()
{
}
