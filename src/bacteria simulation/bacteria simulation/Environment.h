#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include "Bacterium.h"

const int NEIGHBOUR_SIZE = 10;

class Environment
{
public:
	std::vector<Bacterium> bacteria;
	
	Environment();
	~Environment();
	Environment(int size);
	void display();
	void run(int tickNumber);
};

