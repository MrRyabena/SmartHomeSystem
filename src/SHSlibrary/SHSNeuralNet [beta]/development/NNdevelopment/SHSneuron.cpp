#include "SHSneuron.h"
#include <cmath>


double neuron::eta = 0.15; // net learning rate
double neuron::alpha = 0.5; // momentum

 neuron::neuron(uint8_t numOutputs, uint8_t myIndex)
{
	for (uint8_t c = 0; c < numOutputs; ++c) {
		outputWeights.push_back(Connection());
		outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

void neuron::updateInputWeights(Layer &prevLayer)
{
	for (uint8_t n = 0; n < prevLayer.size(); ++n)
	{
		neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight = eta * neuron.getOutputVal() * gradient + alpha * oldDeltaWeight;
		neuron.outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	for (uint8_t n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += outputWeights[n].weight * nextLayer[n].gradient;
	}

	return sum;
}

void neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	gradient = dow * neuron::activationFunctionDerivative(outputVal);
}
void neuron::calcOutputGradients(const double &targetVals)
{
	double delta = targetVals - outputVal;
	gradient = delta * neuron::activationFunctionDerivative(outputVal);
}

double neuron::activationFunction(const double &x)
{
	//output range [-1.0..1.0]
	return tanh(x);
}

double neuron::activationFunctionDerivative(const double &x)
{
	return 1.0 - x * x;
}

void neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	for (uint8_t n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputVal() *
			prevLayer[n].outputWeights[m_myIndex].weight;
	}

	outputVal = neuron::activationFunction(sum);
}