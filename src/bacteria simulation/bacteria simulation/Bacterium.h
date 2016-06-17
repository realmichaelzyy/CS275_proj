#pragma once
#include <vector>
#include <string>
#include <map>
class Bacterium
{
public:
	double positionX, positionY;
	double radius;
	double energy;
	double theta;
	int age;
	int id
	int smartlevel;
	std::vector<std::string> history;
	std::string netfile;

	double getSpeed();
	void move();
	void initialize(int id, int smart);
	void updateDirection(std::vector<Bacterium>& bacteria);
	bool touch(const Bacterium& b);
	double dist(const Bacterium& b);
	std::string getRecord(std::vector<Bacterium>& bacteria);
};
