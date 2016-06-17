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
	Environment(int size);
	void display();
	void run(int tickNumber);
};

