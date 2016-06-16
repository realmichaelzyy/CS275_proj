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
	std::vector<std::string> history;

	double getSpeed();
	void move();
	void initialize();
	void updateDirection(std::vector<Bacterium>& bacteria);
	bool touch(const Bacterium& b);
	double dist(const Bacterium& b);

private:
	void log(std::vector<Bacterium>& bacteria);
};

class SimpleBacterium : Bacterium 
{
public:
	void updateDirection(std::vector<Bacterium>& bacteria);
};