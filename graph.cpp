//Clay Wyers Jared Ford final Proj

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

int citynum; //first line of file
std::vector<std::string> names; //for sure
std::vector<std::vector<int> > connections;
std::vector<std::vector<int> > costs;
std::vector<std::vector<int> > distances;


void directRoutes();
void mst();
void shortestPathMiles(int source, int destination);
void shortestPathPrice(int source, int destination);
void shortestPathHops(int source, int destination);
void tripPriceOptions(int source, double price);
void newRoute(int source, int destination, int cost, int distance);
void deleteRoute(int source, int destination, int cost, int distance);



int main(int argc, char *argv[]) {

	std::string file = argv[1]; //the file name

	/*
	for (int i = 0; i < citynum; i++){
		for (int j = 0; j< citynum; j++){
			connections[i][j] = 9999;
		}
	}


	for (int i = 0; i < citynum; i++){
		for (int j = 0; j< citynum; j++){
			std::cout << connections[i][j] << " ";
		}
		std::cout << "\n";
	}
	*/
	//some of the needed variables
	std::ifstream myfile2;

	std::string currentline;
	std::string stringvalues;

	myfile2.open(file.c_str());
	std::string citynumberstring;
	std::string cityname;
	getline(myfile2, citynumberstring);
	citynum = std::stoi(citynumberstring);
	std::cout << "citynum = " << citynum << "\n";
	for (int k = 0; k < citynum; k++) {
		getline(myfile2, cityname);
		std::cout << cityname << "\n";
		names.push_back(cityname);
	}

connections.resize(citynum);
for (int i = 0; i< connections.size(); i++)
connections[i].resize(citynum);

distances.resize(citynum);
for (int i = 0; i< distances.size(); i++)
distances[i].resize(citynum);

costs.resize(citynum);
for (int i = 0; i< costs.size(); i++)
costs[i].resize(citynum);

for (int i = 0; i < citynum; i++){
	for (int j = 0; j< citynum; j++){
		distances[i][j] = -1;
	}
}

for (int i = 0; i < citynum; i++){
	for (int j = 0; j< citynum; j++){
		costs[i][j] = -1;
	}
}

std::cout << "HERE" << std::endl;


	double firstnum, secondnum, distance, cost;
	while (myfile2 >> firstnum >> secondnum >> distance >> cost) { //get all values, save to a string
  //read line
		std::cout << firstnum << " " << secondnum << " " << distance << " " << cost << std::endl;
		connections[firstnum-1][secondnum-1] = 1;
		connections[secondnum-1][firstnum-1] = 1;
		distances[firstnum-1][secondnum-1] = distance;
		distances[secondnum-1][firstnum-1] = distance;
		costs[firstnum-1][secondnum-1] = cost;
		costs[secondnum-1][firstnum-1] = cost;



	}

	for (int i = 0; i < citynum; i++){
		for (int j = 0; j< citynum; j++){
			std::cout << connections[i][j] << " ";
		}
		std::cout << "\n";
	}
		std::cout << "\n";

	for (int i = 0; i < citynum; i++){
		for (int j = 0; j< citynum; j++){
			std::cout << distances[i][j] << " ";
		}
		std::cout << "\n";
	}
		std::cout << "\n";

	for (int i = 0; i < citynum; i++){
		for (int j = 0; j< citynum; j++){
			std::cout << costs[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	myfile2.close();
	std::cout << "NAMES SIZE = " << names.size() << std::endl;
	for (int j = 0; j < names.size(); j++) {
		std::cout << names[j] << "\n";
	}
	std::cout << "\n";


	//std::cin >> file;
	return 0;
}
