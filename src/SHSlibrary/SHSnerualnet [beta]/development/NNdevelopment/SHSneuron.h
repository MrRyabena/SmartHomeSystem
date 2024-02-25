#pragma once
#include <vector>
#include <stdint.h>

class neuron;

typedef std::vector<neuron> Layer;

struct Connection
{
	double weight{};
	double deltaWeight{};
};

class neuron
{
public:
	neuron(uint8_t numOutputs, uint8_t myIndex);
	void setOutputVal(const double &val) { outputVal = val; }
	double getOutputVal() const { return outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(const double &targetVals);
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);
private:
	static double eta;
	static double alpha;
	static double randomWeight() { return rand() / double(RAND_MAX); }
	static double activationFunction(const double &x);
	static double activationFunctionDerivative(const double &x);
	double sumDOW(const Layer &nextLayer) const;
	double outputVal;
	std::vector<Connection> outputWeights;
	uint8_t m_myIndex{};
	double gradient{};
};