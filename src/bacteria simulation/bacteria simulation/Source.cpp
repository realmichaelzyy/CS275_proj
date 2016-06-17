#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <cmath>
#include <time.h>
using namespace std;

#include "Bacterium.h"
#include "Environment.h"
#include "FANN.h"
#include "Helper.h"

int main() {
	srand (time(NULL));
	int niters = 1;
	Environment base_environment(20, 0, 0.5);
	base_environment.display();
	base_environment.run(100);
	base_environment.CloseFile();
	// for (int iter = 0; iter < niters; iter++) {
	// 	FANN_Train(DataFile, NetFile);
	// 	printf("train completed\n");
	// 	Environment environment(20, 1, 0.5);
	// 	environment.display();
	// 	environment.run(100);
	// }
	printf("Completed!\n");
	// system("pause");
}