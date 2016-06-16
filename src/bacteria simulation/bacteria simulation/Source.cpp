#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <cmath>
using namespace std;

#include "Bacterium.h"
#include "Environment.h"


int main() {
	Environment environment(20);
	environment.display();
	environment.run(100);
	system("pause");
}