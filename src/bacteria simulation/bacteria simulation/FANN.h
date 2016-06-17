#pragma once
#include "floatfann.h"
#include "fann.h"

void FANN_Train(std::string datafile, std::string netfile);

void FANN_Test(std::string netfile, fann_type* input, double& dirX, double& dirY);