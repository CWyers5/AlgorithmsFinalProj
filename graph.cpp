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
void shortestPathHops(int source, int destination); //depth first search
void tripPriceOptions(int source, double price);
void newRoute(int source, int destination, int cost, int distance);
void deleteRoute(int source, int destination);
void help();
void nameOfCities();



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
	for (int i = 0; i < connections.size(); i++)
		connections[i].resize(citynum);

	distances.resize(citynum);
	for (int i = 0; i < distances.size(); i++)
		distances[i].resize(citynum);

	costs.resize(citynum);
	for (int i = 0; i < costs.size(); i++)
		costs[i].resize(citynum);

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
			distances[i][j] = -1;
		}
	}

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
			costs[i][j] = -1;
		}
	}


	double firstnum, secondnum, distance, cost;
	while (myfile2 >> firstnum >> secondnum >> distance >> cost) { //get all values, save to a string
  //read line
		std::cout << firstnum << " " << secondnum << " " << distance << " " << cost << std::endl;
		connections[firstnum - 1][secondnum - 1] = 1;
		connections[secondnum - 1][firstnum - 1] = 1;
		distances[firstnum - 1][secondnum - 1] = distance;
		distances[secondnum - 1][firstnum - 1] = distance;
		costs[firstnum - 1][secondnum - 1] = cost;
		costs[secondnum - 1][firstnum - 1] = cost;

	}

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
			std::cout << connections[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
			std::cout << distances[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
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


	std::cout << "-----------------------------------------------\n";
	std::cout << "|FlightFinder 1.0 by Jared Ford and Clay Wyers|\n";
	std::cout << "-----------------------------------------------\n";
	int input, source, destination, givenPrice, givenCost, givenDistance;
	nameOfCities();
	bool loop = true;
	while (loop) {
		std::cout << "Enter 0 for help\n";
		std::cout << "Enter Command: ";
		std::cin >> input;

		switch(input){
			case 0:
			help();
			break;
			case 1:
			directRoutes();
			break;
			case 2:
			mst();
			break;
			case 3:
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			shortestPathMiles(source,destination);
			break;
			case 4:
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			shortestPathPrice(source,destination);
			break;
			case 5:
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			shortestPathHops(source,destination);
			break;
			case 6:
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Money Amount: ";
			std::cin >> givenPrice;
			tripPriceOptions(source,givenPrice);
			break;
			case 7:
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			std::cout << "\nEnter Cost: ";
			std::cin >> givenCost;
			std::cout << "\nEnter Distance: ";
			std::cin >> givenDistance;
			newRoute(source,destination,givenCost,givenDistance);
			break;
			case 8:
			std::cout << "\nEnter Source";
			std::cin >> source;
			std::cout << "\nEnter Destination";
			std::cin >> destination;
			deleteRoute(source,destination);
			break;
			case 9:
			loop = false;
			break;

		}

	}


	//std::cin >> file;
	return 0;
}

void help(){
	using namespace std;
	cout << "************************************\n";
	cout << "             HELP MENU               \n";
	cout << "Enter 1 to Display Direct Routes\n";
	cout << "Enter 2 for Minimum Spanning Tree\n";
	cout << "Enter 3 for Shortest Path (based on Miles) point A to Point B\n";
	cout << "Enter 4 for Shortest Path (based on Price) point A to Point B\n";
	cout << "Enter 5 for Shortest Path (based on Hops) point A to Point B\n";
	cout << "Enter 6 for all travel options for given money amount\n";
	cout << "Enter 7 to create a new Route between 2 cities\n";
	cout << "Enter 8 to delete a Route between 2 cities\n";
	cout << "Enter 9 to quit\n";
	cout << "*************************************\n";
}

void nameOfCities(){
	std::cout << "Cities Offering Flights and Their Corresponding Number:\n";
	for (int j = 0; j < names.size(); j++) {
		std::cout << names[j] << " - " << j + 1 << "\n";
	}
	std::cout << "\n";

}

void directRoutes(){}
void mst(){}
void shortestPathMiles(int source, int destination){}
void shortestPathPrice(int source, int destination){}
void shortestPathHops(int source, int destination){} //depth first search
void tripPriceOptions(int source, double price){}
void newRoute(int source, int destination, int cost, int distance){}
void deleteRoute(int source, int destination){}
