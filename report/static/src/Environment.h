#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <fstream>
#include <map>
#include "Bacterium.h"

class Environment
{
public:
	std::vector<Bacterium> bacteria;
	std::map<int, std::vector<std::string> > history;
	std::ofstream fout, log;
	int count;
	Environment();
	~Environment();
	Environment(int size, int num_smart, double prob_naive);
	void display();
	void run(int tickNumber);
	void CloseFile();
};

