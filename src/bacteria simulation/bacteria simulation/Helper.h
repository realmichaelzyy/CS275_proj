#pragma once


#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>


const double BASE_SIZE = 1.0 / 15;
const double BASE_SPEED = 1.0 / 10;
const int NEIGHBOUR_SIZE = 10;

std::default_random_engine generator;
std::uniform_real_distribution<double> uniform(0.0, 1.0);
std::geometric_distribution<int> geometric(0.6);
