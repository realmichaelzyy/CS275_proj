#define _USE_MATH_DEFINES

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <cmath>
using namespace std;


/*
This part is for configuration purpose
*/
const double BASE_SIZE = 1.0 / 500;
const double BASE_SPEED = 1.0 / 100;
default_random_engine generator;
uniform_real_distribution<double> uniform(0.0, 1.0);
geometric_distribution<int> geometric(0.6);


/*
Bacterium
*/
class Bacterium {	
public:
	double positionX, positionY;
	double directionX, directionY;
	double radius;
	void move() {
		positionX += directionX;
		positionY += directionY;
		if (positionX > 1 || positionX < 0) directionX = -directionX;
		if (positionY > 1 || positionY < 0) directionY = -directionY;
	}

	void initialize() {
		positionX = uniform(generator);
		positionY = uniform(generator);
		radius = (1 + geometric(generator)) * BASE_SIZE;
	}

	void updateDirection(Environment* pEnvironment) {
		double theta = (uniform(generator) - 0.5) * 2 * M_PI;
		double speed = BASE_SPEED / (radius / BASE_SIZE);
		directionX = speed * cos(theta);
		directionY = speed * sin(theta);
	}

	bool touch(const Bacterium& b) {
		return (radius + b.radius) * (radius + b.radius) >
			(positionX - b.positionX) * (positionX - b.positionX) +
			(positionY - b.positionY) * (positionY - b.positionY);
	}
};

/*
Environment
*/
class Environment {
public:
	vector<Bacterium> bacteria;
	Environment(int size) {
		bacteria.clear();
		for (int k = 0; k < size; ++k) {
			Bacterium bacterium;
			bacterium.initialize();
			bacteria.push_back(bacterium);
		}
	}
	void display() {
		for (int k = 0; k < bacteria.size(); ++k) {
			Bacterium& b = bacteria[k];
			cout << b.positionX << " " << b.positionY << " " << b.radius << endl;
		}
	}

	void run(int tickNumber) {
		for (int tick = 0; tick < tickNumber; ++tick) {
			for (int i = 0; i < bacteria.size(); ++i) {
				Bacterium& b = bacteria[i];
				b.updateDirection(this);
			}
			for (int i = 0; i < bacteria.size(); ++i) {
				Bacterium& b = bacteria[i];
				b.move();
			}
			vector<Bacterium> newBacteria;
			vector<bool> visited(bacteria.size(), false);
			for (int i = 0; i < bacteria.size(); ++i) {
				Bacterium b = bacteria[i];
				for (int j = i + 1; j < bacteria.size(); ++j) {
					if (visited[j]) continue;
					Bacterium& t = bacteria[j];
					if (b.touch(t)) {
						Bacterium newB = b.radius > t.radius ? b : t;
						newB.radius = sqrt(b.radius * b.radius + t.radius * t.radius);
						b = newB;
						visited[j] = false;
					}
					newBacteria.push_back(b);
				}
			}
			bacteria = newBacteria;
		}
	}
};

int main() {
	Environment environment(20);
	environment.display();
	system("pause");
}