// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ANNLayer.h"
/**
 * 
 */
class PONG_UE5_ANN_API ANN
{
public:
	int NumInputs;
	int NumOutputs;
	int NumHidden;
	int NumNeuronsPerHidden;
	double Alpha;
	TArray<ANNLayer> Layers;

	ANN(int InInputs, int InOutputs, int InHidden, int InPerHidden, double InAlpha);

	TArray<double> Train(const TArray<double>& InputValues, const TArray<double>& DesiredOutput);
	TArray<double> CalcOutput(const TArray<double>& InputValues);
	FString PrintWeights() const;
	void LoadWeights(const FString& WeightString);
	ANN();
	~ANN();
private:
	void UpdateWeights(const TArray<double>& Outputs, const TArray<double>& DesiredOutput);
	double ActivationFunction(double Value) const;
	double Tanh(double Value) const;
	double Sigmoid(double Value) const;
	double Identity(double Value) const;
};
