#pragma once
#include <vector>
#include <stdint.h>
#include "SHSeasyVector.h"


class net
{
public:
	net(const std::vector<uint8_t> &topology);
	void feedForward(const std::vector<double> &inputVals);
	void backProp(const std::vector<double> &targetVals);
	void getResults(std::vector<double> &resultVals) const;
	double getRecentAverageError() const { return recentAverageError; }
private:
	std::vector<Layer> layers;//layers[layerNumber][NeuronNumber]
	double error{};
	double recentAverageError{};
	static double recentAverageSmoothingFactor;
};
