// Fill out your copyright notice in the Description page of Project Settings.


#include "ANN.h"

ANN::ANN(int InInputs, int InOutputs, int InHidden, int InPerHidden, double InAlpha)
	: NumInputs(InInputs), NumOutputs(InOutputs), NumHidden(InHidden), NumNeuronsPerHidden(InPerHidden), Alpha(InAlpha)
{
	if (NumHidden > 0)
	{
		Layers.Add(ANNLayer(NumNeuronsPerHidden, NumInputs));
		for (int i = 0; i < NumHidden - 1; ++i)
		{
			Layers.Add(ANNLayer(NumNeuronsPerHidden, NumNeuronsPerHidden));
		}
		Layers.Add(ANNLayer(NumOutputs, NumNeuronsPerHidden));
	}
	else
	{
		Layers.Add(ANNLayer(NumOutputs, NumInputs));
	}
}

TArray<double> ANN::Train(const TArray<double>& InputValues, const TArray<double>& DesiredOutput)
{
	auto Outputs = CalcOutput(InputValues);
	UpdateWeights(Outputs, DesiredOutput);
	return Outputs;
}

TArray<double> ANN::CalcOutput(const TArray<double>& InputValues)
{
	TArray<double> Inputs = InputValues;
	TArray<double> Outputs;

	if (Inputs.Num() != NumInputs)
	{
		UE_LOG(LogTemp, Error, TEXT("Incorrect input count: expected %d"), NumInputs);
		return Outputs;
	}

	for (int i = 0; i < Layers.Num(); ++i)
	{
		if (i > 0)
			Inputs = Outputs;
		Outputs.Empty();

		for (ANNNeuron& Neuron : Layers[i].Neurons)
		{
			Neuron.Inputs = Inputs;
			double N = 0.0;
			for (int k = 0; k < Neuron.NumInputs; ++k)
				N += Neuron.Weights[k] * Neuron.Inputs[k];

			N -= Neuron.Bias;
			Neuron.Output = ActivationFunction(N);
			Outputs.Add(Neuron.Output);
		}
	}
	return Outputs;
}

void ANN::UpdateWeights(const TArray<double>& Outputs, const TArray<double>& DesiredOutput)
{
	for (int i = NumHidden; i >= 0; --i)
	{
		for (int j = 0; j < Layers[i].NumNeurons; ++j)
		{
			auto& Neuron = Layers[i].Neurons[j];

			if (i == NumHidden)
			{
				double Error = DesiredOutput[j] - Outputs[j];
				Neuron.ErrorGradient = Neuron.Output * (1 - Neuron.Output) * Error;
			}
			else
			{
				Neuron.ErrorGradient = Neuron.Output * (1 - Neuron.Output);
				double GradientSum = 0.0;
				for (ANNNeuron& NextNeuron : Layers[i + 1].Neurons)
					GradientSum += NextNeuron.ErrorGradient * NextNeuron.Weights[j];

				Neuron.ErrorGradient *= GradientSum;
			}

			for (int k = 0; k < Neuron.NumInputs; ++k)
			{
				double InputVal = Neuron.Inputs[k];
				if (i == NumHidden)
				{
					double Error = DesiredOutput[j] - Outputs[j];
					Neuron.Weights[k] += Alpha * InputVal * Error;
				}
				else
				{
					Neuron.Weights[k] += Alpha * InputVal * Neuron.ErrorGradient;
				}
			}
			Neuron.Bias += Alpha * -Neuron.ErrorGradient;
		}
	}
}

FString ANN::PrintWeights() const
{
	FString WeightStr;
	for (const ANNLayer& Layer : Layers)
	{
		for (const ANNNeuron& Neuron : Layer.Neurons)
		{
			for (double W : Neuron.Weights)
			{
				WeightStr += FString::SanitizeFloat(W) + TEXT(",");
			}
		}
	}
	return WeightStr;
}

void ANN::LoadWeights(const FString& WeightString)
{
	if (WeightString.IsEmpty()) return;

	TArray<FString> WeightArray;
	WeightString.ParseIntoArray(WeightArray, TEXT(","), true);

	int w = 0;
	for (ANNLayer& Layer : Layers)
	{
		for (ANNNeuron& Neuron : Layer.Neurons)
		{
			for (int i = 0; i < Neuron.NumInputs; ++i)
			{
				if (w < WeightArray.Num())
					Neuron.Weights[i] = FCString::Atod(*WeightArray[w++]);
			}
		}
	}
}

double ANN::ActivationFunction(double Value) const
{
	return Tanh(Value);
}

double ANN::Tanh(double Value) const
{
	return 2.0 / (1.0 + FMath::Exp(-2.0 * Value)) - 1.0;
}

double ANN::Sigmoid(double Value) const
{
	return 1.0 / (1.0 + FMath::Exp(-Value));
}

double ANN::Identity(double Value) const
{
	return Value;
}

ANN::ANN()
{
}

ANN::~ANN()
{
}
