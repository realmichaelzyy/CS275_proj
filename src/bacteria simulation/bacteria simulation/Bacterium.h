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
	int id;

	double getSpeed();
	void move();
	void initialize(int id);
	void updateDirection(std::vector<Bacterium>& bacteria);
	bool touch(const Bacterium& b);
	double dist(const Bacterium& b);
	std::string getRecord(std::vector<Bacterium>& bacteria);
};

class NaiveBacterium : Bacterium 
{
public:
	void updateDirection(std::vector<Bacterium>& bacteria);
};

class SmartBacterium : Bacterium
{
public:
	std::string netfile;
	void updateDirection(std::vector<Bacterium>& bacteria);
};