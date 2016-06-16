#include "Environment.h"

using namespace std;

Environment::Environment()
{
}

Environment::Environment(int size) {
	bacteria.clear();
	for (int k = 0; k < size; ++k) {
		Bacterium bacterium;
		bacterium.initialize();
		bacteria.push_back(bacterium);
	}
}

Environment::~Environment()
{
}

void Environment::display() {
	for (int k = 0; k < bacteria.size(); ++k) {
		Bacterium& b = bacteria[k];
		std::cout << b.positionX << " " << b.positionY << " " << b.radius << std::endl;
	}
}

void Environment::run(int tickNumber) {
	for (int tick = 0; tick < tickNumber; ++tick) {
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			b.updateDirection();
		}
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			b.move();
		}
		vector<Bacterium> newBacteria;
		vector<bool> visited(bacteria.size(), false);
		for (int i = 0; i < bacteria.size(); ++i) {
			if (visited[i]) continue;
			Bacterium b = bacteria[i];
			for (int j = i + 1; j < bacteria.size(); ++j) {
				if (visited[j]) continue;
				Bacterium& t = bacteria[j];
				if (b.touch(t)) {
					Bacterium newB = b.radius > t.radius ? b : t;
					newB.radius = sqrt(b.radius * b.radius + t.radius * t.radius);
					b = newB;
					visited[j] = true;
					
				}
			}
			newBacteria.push_back(b);
		}
		bacteria = newBacteria;
		display();
		system("pause");
	}
	
}