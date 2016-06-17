#define _USE_MATH_DEFINES

#include "Bacterium.h"
#include "Helper.h"
#include <cmath>
#include <sstream>
#include <climits>

#if !defined(_WIN32)
#include "FANN.h"
#endif

using namespace std;

std::default_random_engine generator;
std::uniform_real_distribution<double> uniform(0.0, 1.0);
std::geometric_distribution<int> geometric(0.6);

double Bacterium::getSpeed() {
	return BASE_SPEED / (radius / BASE_SIZE);
}

string Bacterium::getRecord(vector<Bacterium>& bacteria) {
	stringstream ss;
	ss << radius;
	for (int i = 0; i < bacteria.size(); ++i) {
		ss << " " << bacteria[i].positionX - positionX << " " << bacteria[i].positionY - positionY << " " << bacteria[i].radius;
	}
	ss << endl;
	ss << cos(theta) << " " << sin(theta) << endl;
	return ss.str();
}

void Bacterium::move() {

	double speed = getSpeed();
	double directionX = speed * cos(theta);
	double directionY = speed * sin(theta);
	if (positionX + directionX > 1 || positionX + directionX < 0) directionX = -directionX;
	if (positionY + directionY > 1 || positionY + directionY < 0) directionY = -directionY;
	positionX += directionX;
	positionY += directionY;

	energy -= radius * radius * 0.01 * radius / BASE_SIZE;
	++age;
}


void Bacterium::initialize(int id, int smart) {
	smartlevel = smart;
	netfile = NetFile;
	this->id = id;
	positionX = uniform(generator);
	positionY = uniform(generator);
	radius = (1 + geometric(generator)) * BASE_SIZE;
	energy = radius * radius;
	theta = (uniform(generator) - 0.5) * 2 * M_PI;
	age = 0;
}

void Bacterium::updateDirection(vector<Bacterium>& bacteria) {
	if (uniform(generator) < 0.7) {
		return;
	}
	theta = (uniform(generator) - 0.5) * 2 * M_PI;
	if (smartlevel == 1) {
		double mindist = INT_MAX;
		for (int i = 0; i < bacteria.size(); i++)
		{
			if ((bacteria[i].radius > radius) && (dist(bacteria[i]) < mindist)) {
				mindist = dist(bacteria[i]);
				double dy = positionY - bacteria[i].positionY;
				double dx = positionX - bacteria[i].positionX;
				theta = atan2(dy, dx);
			}
		}
	} 
	#if !defined(_WIN32)
	else if (smartlevel == 2) {
		fann_type* input = new fann_type[NEIGHBOUR_SIZE * 3 + 1];
		input[0] = radius;
		for (int i = 0; i < bacteria.size(); i++)
		{
			input[3 * i + 1] = bacteria[i].positionX - positionX;
			input[3 * i + 2] = bacteria[i].positionY - positionY;
			input[3 * i + 3] = bacteria[i].radius;
		}
		fann_type *result = FANN_Test(netfile, input);
		theta = atan(result[1] / result[0]);
		delete[] input;
	}
	#endif
}

bool Bacterium::touch(const Bacterium& b) {
	return (radius + b.radius) * (radius + b.radius) >
		(positionX - b.positionX) * (positionX - b.positionX) +
		(positionY - b.positionY) * (positionY - b.positionY);
}

double Bacterium::dist(const Bacterium& b) {
	return sqrt(
		(positionX - b.positionX) * (positionX - b.positionX) + 
		(positionY - b.positionY) * (positionY - b.positionY));
}

