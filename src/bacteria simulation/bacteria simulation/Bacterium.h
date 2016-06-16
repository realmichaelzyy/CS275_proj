#pragma 

class Bacterium
{
public:
	double positionX, positionY;
	double directionX, directionY;
	double radius;

	void move();
	void initialize();
	void updateDirection(const vector<Bacterium> bacteria);
	bool touch(const Bacterium& b);
	double dist(const Bacterium b);
};

class SimpleBacterium : Bacterium 
{
pulic:
	void updateDirection(const vector<Bacterium> bacteria);
}