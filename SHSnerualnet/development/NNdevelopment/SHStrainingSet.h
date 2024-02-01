#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "SHSeasyVector.h"

class trainingSet
{
public:
	trainingSet(const std::string filename);
	bool isEOF() { return trainingDataFile.eof(); }
	void getTopology(std::vector<uint8_t> &topology);
	unsigned getNextInputs(std::vector<double> &inputVals);
	unsigned getTargetOutputs(std::vector<double> &targetOutputVals);
private:
	std::ifstream trainingDataFile;
};
