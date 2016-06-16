#pragma once
#include <vector>

class Bacterium
{
public:
	double positionX, positionY;
	double radius;
	double theta;

	double getSpeed();
	void move();
	void initialize();
	void updateDirection(std::vector<Bacterium>& bacteria);
	bool touch(const Bacterium& b);
};
