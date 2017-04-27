//Clay Wyers Jared Ford final Proj
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

int citynum; //first line of file
std::vector<std::string> names; //for sure
std::vector<std::vector<int> > connections;
std::vector<std::vector<int> > costs;
std::vector<std::vector<int> > distances;


void directRoutes();
void mst();
void shortestPathMiles(int source, int destination);
void shortestPathPrice(int source, int destination);
void shortestPathHops(int source, int destination); //breadth first search
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
	bool routesChanged = false; //only worry about rewriting file if its changed
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
			nameOfCities();
			std::cout << "Adding a Route\n";
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			std::cout << "\nEnter Cost: ";
			std::cin >> givenCost;
			std::cout << "\nEnter Distance: ";
			std::cin >> givenDistance;
			newRoute(source,destination,givenCost,givenDistance);
			routesChanged = true;
			break;
			case 8:
			nameOfCities();
			std::cout << "Deleting a route\n";
			std::cout << "\nEnter Source: ";
			std::cin >> source;
			std::cout << "\nEnter Destination: ";
			std::cin >> destination;
			deleteRoute(source,destination);
			routesChanged = true;
			break;
			case 9:
			loop = false;
			break;
			default:
			std::cout << "Bad Command Given\n";
			break;

		}

	}


	//newRoute() and deleteRoute() change this bool to true, and so we rewrite the file
if (routesChanged){

	std::ofstream myfile;
  myfile.open (file.c_str());
	myfile << citynum << std::endl; //write number of cities
	for (int i = 0; i < names.size(); i++){
		myfile << names[i] << std::endl; //write the names of cities to file
	}
	for (int k = 0; k < citynum; k++){
		for (int p = k; p < citynum; p++){
			/*routes are listed with lower number first, by starting at i,
			we avoid listing a route twice, i think */
			if (connections[k][p] == 1){
				myfile << k+1 << " " << p+1 << " " << distances[k][p] << " " << costs[k][p] << ".00" << std::endl;
			}
		}
	}
  myfile.close(); //file is written correctly and closed, rewritten files can be reread
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


void mst(){}
void shortestPathMiles(int source, int destination){}
void shortestPathPrice(int source, int destination){}


void shortestPathHops(int source, int destination){

	std::vector<bool> visited(citynum); //track where I've been
	std::vector<int> parents(citynum); //track who I came from to form the path
	for (int i = 0; i < visited.size(); i++)
		visited[i] = false;
	for (int i = 0; i < parents.size(); i++)
		parents[i] = -1;

	if (source == destination) //duh case
	  std::cout << "Source and Destination are the same, no travel needed\n";
	else{

		int start = destination-1; //start at destination so we can work backwards later
	  std::queue<int>  Q;
		visited[destination-1] = true;
	  Q.push(start);
	while (!Q.empty()){ //googled BFS and its pretty standard
		int current = Q.front(); //current node
		Q.pop(); //pop it
		for (int i = 0; i < citynum; i++){

	     if (connections[current][i] == 1 && visited[i] == false){
					visited[i] = true;
					parents[i] = current;

	     		if ( current != source-1){ //if not source, push to queue
						//if it is source, than the queue will end up being empty, and we move on
	      		Q.push(i);
	     		}
	   	}
		}
	}
	/*print the path, starting from source and following parents[] which works like a pointer
	a little shifty, should probably have a check to see if 2 nodes are connected at all.
	the domestic file is 100% connected, so no chance of issues there. */
	std::cout << "Shortest Path from " << names[source-1] << " to " << names[destination-1] << "\n";
	int h = source-1;
	while (h != destination-1){
		std::cout << names[h] << " -> ";
		h = parents[h];
	}
	std::cout << names[destination-1] << "\n";
	}
}



void tripPriceOptions(int source, double price){}

void newRoute(int source, int destination, int cost, int distance){
	if (connections[source-1][destination-1] == 1){
		std::cout << "Error: there is already a route here!\n";
	}
	else {
		connections[source-1][destination-1] = 1;
		connections[destination-1][source-1] = 1;
		costs[source-1][destination-1] = cost;
		costs[source-1][destination-1] = cost;
		distances[source-1][destination-1] = distance;
		distances[destination-1][source-1] = distance;
	}

}

void deleteRoute(int source, int destination){
	if (connections[source-1][destination-1] == 0){
		std::cout << "Error: there is no route here to remove\n";
	}
	else {
		connections[source-1][destination-1] = 0;
		connections[destination-1][source-1] = 0;
		costs[source-1][destination-1] = -1;
		costs[source-1][destination-1] = -1;
		distances[source-1][destination-1] = -1;
		distances[destination-1][source-1] = -1;
	}

}

void directRoutes() {
	int maxLen = 0;
	for (std::string s : names) {
		maxLen = s.length() > maxLen ? s.length() : maxLen;
	}
	for (int i = 0; i < names.size(); i++)
	{
		for (int j = 0; j < names.size(); j++)
		{
			if (connections[i][j] == 1) {
				std::cout << std::setw(maxLen) << std::left
					<< names[i];
				std::cout << " -> " << std::setw(maxLen) << std::left
					<<  names[j] << '\t';
				std::cout << "$" << distances[i][j] << '\t'
					<< costs[i][j] << " mi\n";
			}
		}
	}
}
