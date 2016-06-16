#define _USE_MATH_DEFINES
#include "Bacterium.h"
#include "Helper.h"

using namespace std;

void Bacterium::move() {
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

void Bacterium::updateDirection() {
	double theta = (uniform(generator) - 0.5) * 2 * M_PI;
	double speed = BASE_SPEED / (radius / BASE_SIZE);
	directionX = speed * cos(theta);
	directionY = speed * sin(theta);
}

bool Bacterium::touch(const Bacterium& b) {
	return (radius + b.radius) * (radius + b.radius) >
		(positionX - b.positionX) * (positionX - b.positionX) +
		(positionY - b.positionY) * (positionY - b.positionY);
}