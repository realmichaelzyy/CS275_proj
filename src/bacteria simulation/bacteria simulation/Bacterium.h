#pragma once
#include <vector>
#include <string>

class Bacterium
{
public:
	double positionX, positionY;
	double radius;
	double energy;
	double theta;
	int age;
	int smartlevel;
	std::vector<std::string> history;
	std::string netfile;

	double getSpeed();
	void move();
	void initialize(int smart);
	void updateDirection(std::vector<Bacterium>& bacteria);
	bool touch(const Bacterium& b);
	double dist(const Bacterium& b);
	void log(std::vector<Bacterium>& bacteria);
};
