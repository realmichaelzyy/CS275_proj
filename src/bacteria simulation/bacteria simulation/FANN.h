#pragma once
#include "floatfann.h"
#include "fann.h"

void FANN_Train(std::string datafile, std::string netfile);

fann_type* FANN_Test(std::string netfile, fann_type* input);