#include "Environment.h"
#include "Helper.h"
using namespace std;

Environment::Environment()
{
	
}

Environment::Environment(int size) {
	fout.open("test.txt", std::fstream::out);
	bacteria.clear();
	for (int k = 0; k < size; ++k) {
		Bacterium bacterium;
		bacterium.initialize();
		bacteria.push_back(bacterium);
	}
}

Environment::~Environment()
{
	fout.close();
}

void Environment::display() {
	for (int k = 0; k < bacteria.size(); ++k) {
		Bacterium& b = bacteria[k];
		std::cout << b.positionX << " " << b.positionY << " " << b.radius << " " << b.energy / b.radius / b.radius << " " << b.age << std::endl;
	}
}

void Environment::run(int tickNumber) {
	vector<Bacterium> winner;

	for (int tick = 0; tick < tickNumber; ++tick) {
		
		// Add bacteria when not enough
		while (bacteria.size() <= NEIGHBOUR_SIZE) {
			Bacterium b;
			b.initialize();
			bacteria.push_back(b);
		}

		// move bacteria with information of nearest 10(changable) neighbours
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			vector<Bacterium> neighbours;
			vector<bool> visited(bacteria.size(), false);
			visited[i] = true;

			for (int k = 0; k < NEIGHBOUR_SIZE; ++k) {
				double min_dis = 2;
				int choice = -1;
				for (int j = 0; j < bacteria.size(); ++j) {
					if (visited[j]) continue;
					double dis = b.dist(bacteria[j]);
					if (dis < min_dis) {
						min_dis = dis;
						choice = j;
					}
				}
				neighbours.push_back(bacteria[choice]);
				visited[choice] = true;
			}
			b.updateDirection(neighbours);
		}


		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			b.log(bacteria);
			b.move();
		}

		// merge bacteria 
		vector<Bacterium> newBacteria;
		vector<bool> visited(bacteria.size(), false);

		// eliminate all bacteria with negative energy
		for (int i = 0; i < bacteria.size(); ++i) {
			if (bacteria[i].energy < 0) {
				visited[i] = true;
				
				// log 
				winner.push_back(bacteria[i]);
				int k = bacteria.size() - 1;
				while (k > 0 && bacteria[k].age > bacteria[k - 1].age) {
					swap(bacteria[k], bacteria[k - 1]);
					--k;
				}
				if (winner.size() > 10) winner.pop_back();
			}
		}

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
	}
	
	int sampleCount = 0;
	for (int i = 0; i < winner.size(); ++i) {
		Bacterium b = winner[i];
		sampleCount += winner[i].history.size();
	}
	fout << sampleCount << " " << 31 << " " << 1 << endl;
	for (int i = 0; i < winner.size(); ++i) {
		Bacterium b = winner[i];
		for (int i = 0; i < b.history.size(); ++i) {
			fout << b.history[i];
		}
	}
	fout.flush();
}