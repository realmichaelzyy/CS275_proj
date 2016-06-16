#include "floatfann.h"
#include "fann.h"

void FANN_Train(string datafile, string netfile);

fann_type* FANN_Test(string netfile, fann_type* input);