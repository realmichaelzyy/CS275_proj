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
	double dist(const Bacterium b);
};

class SimpleBacterium : Bacterium 
{
public:
	void updateDirection(const vector<Bacterium> bacteria);
};