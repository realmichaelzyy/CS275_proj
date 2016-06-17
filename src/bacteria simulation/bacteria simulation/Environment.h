#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <fstream>
#include "Bacterium.h"

class Environment
{
public:
	std::vector<Bacterium> bacteria;
	std::ofstream fout;
	Environment();
	~Environment();
	Environment(int size, int num_smart, double prob_naive);
	void display();
	void run(int tickNumber);
	void CloseFile();
};

