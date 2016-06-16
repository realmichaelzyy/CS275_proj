#define _USE_MATH_DEFINES
#include "Bacterium.h"
#include "Helper.h"
#include <cmath>

using namespace std;

double Bacterium::getSpeed() {
	return BASE_SPEED / (radius / BASE_SIZE);
}

void Bacterium::move() {
	double speed = getSpeed();
	double directionX = speed * cos(theta);
	double directionY = speed * sin(theta);
	positionX += directionX;
	positionY += directionY;
	if (positionX > 1 || positionX < 0) directionX = -directionX;
	if (positionY > 1 || positionY < 0) directionY = -directionY;
}

void Bacterium::initialize() {
	positionX = uniform(generator);
	positionY = uniform(generator);
	radius = (1 + geometric(generator)) * BASE_SIZE;
}

void Bacterium::updateDirection(vector<Bacterium>& bacteria) {
	theta = (uniform(generator) - 0.5) * 2 * M_PI;
}

bool Bacterium::touch(const Bacterium& b) {
	return (radius + b.radius) * (radius + b.radius) >
		(positionX - b.positionX) * (positionX - b.positionX) +
		(positionY - b.positionY) * (positionY - b.positionY);
}

bool Bacterium::dist(const Bacterium& b) {
	return sqrt(
		(positionX - b.positionX) * (positionX - b.positionX) + 
		(positionY - b.positionY) * (positionY - b.positionY));
}

void SimpleBacterium::updateDirection(const vector<Bacterium> bacteria) {

}