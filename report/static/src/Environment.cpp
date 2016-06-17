#include "Environment.h"
#include "Helper.h"
using namespace std;

Environment::Environment()
{
	
}

Environment::Environment(int size, int num_smart = 0, double prob_naive = 0) {
	fout.open(DataFile.c_str(), std::fstream::out);
	log.open("log.txt", std::fstream::out);
	bacteria.clear();
	double rd = ((double) rand() / (RAND_MAX));
	for (int k = 0; k < size - num_smart; ++k) {
		Bacterium bacterium;
		if (rd < prob_naive)
			bacterium.initialize(count++, 1);
		else
			bacterium.initialize(count++, 0);
		bacteria.push_back(bacterium);
	}
	for (int k = 0; k < num_smart; ++k) {
		Bacterium bacterium;
		bacterium.initialize(count++, 2);
		bacteria.push_back(bacterium);
	}
}

Environment::~Environment()
{
	fout.close();
	log.close();
}

void Environment::CloseFile()
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
	double sum1 = 0, sum2 = 0;
	int cnt1 = 0, cnt2 = 0;

	for (int tick = 0; tick < tickNumber; ++tick) {
		
		// Add bacteria when not enough
		while (bacteria.size() <= NEIGHBOUR_SIZE) {
			Bacterium b;
			b.initialize((count++), 3);
			bacteria.push_back(b);
		}

		// move bacteria with information of nearest 10(changable) neighbours
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			vector<Bacterium> neighbours;
			vector<bool> visited(bacteria.size(), false);
			visited[i] = true;

			for (int k = 0; k < NEIGHBOUR_SIZE; ++k) {
				double min_dis = 1000;
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
			history[b.id].push_back(b.getRecord(neighbours));
		}

		// Log
		//log << bacteria.size() << endl;
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
			//log << b.id << " " << b.positionX << " " << b.positionY << " " << b.radius << " " << b.energy/b.radius/b.radius << " " << b.age << endl;
			log << b.id << " " << b.positionX << " " << b.positionY << " " << b.radius << " " << b.energy / b.radius / b.radius << " ";
		}
		log << endl;
		//
		for (int i = 0; i < bacteria.size(); ++i) {
			Bacterium& b = bacteria[i];
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
				if (winner.size() > tickNumber / 10) winner.pop_back();
				if (bacteria[i].id > 0) {
					sum1 += bacteria[i].age;
					++cnt1;
				} else {
					sum2 += bacteria[i].age;
					++cnt2;
				}
			}
		}

		for (int i = 0; i < bacteria.size(); ++i) {
			if (visited[i]) continue;
			Bacterium b = bacteria[i];

			for (int j = 0; j < bacteria.size(); ++j) {
				if (i == j || visited[j]) continue;
				Bacterium& t = bacteria[j];
				if (b.touch(t)) {
					//cout << b.positionX << " " << b.positionY << " " << b.radius << endl;
					//cout << t.positionX << " " << t.positionY << " " << t.radius << endl;
					Bacterium newB = b.radius > t.radius ? b : t;
					Bacterium prey = b.radius > t.radius ? t : b;
					newB.radius = sqrt(b.radius * b.radius + t.radius * t.radius);
					newB.energy = b.radius > t.radius ? b.energy + t.radius * t.radius : t.energy + b.radius * b.radius;
					b = newB;
					visited[j] = true;

					winner.push_back(prey);
					int k = bacteria.size() - 1;
					while (k > 0 && bacteria[k].age > bacteria[k - 1].age) {
						swap(bacteria[k], bacteria[k - 1]);
						--k;
					}
					if (winner.size() > tickNumber / 10) winner.pop_back();
					if (prey.id > 0) {
						sum1 += prey.age;
						++cnt1;
					}
					else {
						sum2 += prey.age;
						++cnt2;
					}
					//system("pause");
				}
			}
			newBacteria.push_back(b);
		}
		bacteria = newBacteria;
		// display();
		//cout << "~~~~~~~" << endl;
		cout << "!!" << cnt1 << " " << sum1 << " " << sum1 / cnt1 << endl;
		cout << "!!" << cnt2 << " " << sum2 << " " << sum2 / cnt2 << endl;
		//system("pause");
	}
	
	int sampleCount = 0;
	for (int i = 0; i < winner.size(); ++i) {
		Bacterium& b = winner[i];
		sampleCount += history[winner[i].id].size();
	}
	fout << sampleCount << " " << 41 << " " << 2 << endl;
	for (int i = 0; i < winner.size(); ++i) {
		Bacterium& b = winner[i];
		vector<string>& his = history[winner[i].id];
		for (int i = 0; i < his.size(); ++i) {
			fout << his[i];
		}
	}
	fout.flush();
}
