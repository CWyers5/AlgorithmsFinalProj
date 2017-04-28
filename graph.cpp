//Clay Wyers Jared Ford final Proj
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#define INFINITE 999999; //larger than any distance we will use

int citynum; //first line of file
std::vector<std::string> names; //for sure
std::vector<std::vector<int> > connections;
std::vector<std::vector<double> > costs;
std::vector<std::vector<double> > distances;
const std::string ENTER_SOURCE = "Enter Source: ";
const std::string ENTER_DEST = "Enter Destination: ";


void directRoutes();
void mst();
void shortestPathMiles(int source, int destination);
void shortestPathPrice(int source, int destination);
void shortestPathHops(int source, int destination); //breadth first search
void tripPriceOptions(int source, double price);
void newRoute(int source, int destination, double cost, double distance);
void deleteRoute(int source, int destination);
void help();
void nameOfCities();
int getCity(std::string);



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
	//std::cout << "citynum = " << citynum << "\n";
	for (int k = 0; k < citynum; k++) {
		getline(myfile2, cityname);
		//std::cout << cityname << "\n";
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
			distances[i][j] = INFINITE;
		}
	}

	for (int i = 0; i < citynum; i++) {
		for (int j = 0; j < citynum; j++) {
			costs[i][j] = INFINITE;
		}
	}


	int firstnum, secondnum;
	double distance, cost;
	while (myfile2 >> firstnum >> secondnum >> distance >> cost) { //get all values, save to a string
  //read line
		//std::cout << firstnum << " " << secondnum << " " << distance << " " << cost << std::endl;
		--firstnum;
		--secondnum;
		connections[firstnum][secondnum] = 1;
		connections[secondnum][firstnum] = 1;
		distances[firstnum][secondnum] = distance;
		distances[secondnum][firstnum] = distance;
		costs[firstnum][secondnum] = cost;
		costs[secondnum][firstnum] = cost;

	}
	/*
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
	*/

	myfile2.close();
	/*
	std::cout << "NAMES SIZE = " << names.size() << std::endl;
	for (int j = 0; j < names.size(); j++) {
		std::cout << names[j] << "\n";
	}
	std::cout << "\n";
	*/


	std::cout << "-----------------------------------------------\n";
	std::cout << "|FlightFinder 1.0 by Jared Ford and Clay Wyers|\n";
	std::cout << "-----------------------------------------------\n";
	int input, givenPrice, givenCost, givenDistance, source, destination;
	nameOfCities();
	bool loop = true;
	bool routesChanged = false; //only worry about rewriting file if its changed
	while (loop) {
		std::cout << "Enter 0 for help\n";
		std::cout << "Enter Command: ";
		std::cin >> input;

		switch (input) {
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
			nameOfCities();
			source = getCity(ENTER_SOURCE);
			destination = getCity(ENTER_DEST);
			shortestPathMiles(source, destination);
			break;
		case 4:
			nameOfCities(); //this helps users spell city names
			source = getCity(ENTER_SOURCE);
			destination = getCity(ENTER_DEST);
			shortestPathPrice(source, destination);
			break;
		case 5:
			nameOfCities();
			source = getCity(ENTER_SOURCE);
			destination = getCity(ENTER_DEST);
			shortestPathHops(source, destination);
			break;
		case 6:
			nameOfCities();
			source = getCity(ENTER_SOURCE);
			std::cout << "\nEnter Money Amount: ";
			std::cin >> givenPrice;
			tripPriceOptions(source, givenPrice);
			break;
		case 7:
			nameOfCities();
			std::cout << "Adding a Route\n";
			source = getCity(ENTER_SOURCE);
			destination = getCity(ENTER_DEST);
			std::cout << "\nEnter Cost: ";
			std::cin >> givenCost;
			std::cout << "\nEnter Distance: ";
			std::cin >> givenDistance;
			newRoute(source, destination, givenCost, givenDistance);
			routesChanged = true;
			break;
		case 8:
			nameOfCities();
			std::cout << "Deleting a route\n";
			source = getCity(ENTER_SOURCE);
			destination = getCity(ENTER_DEST);
			deleteRoute(source, destination);
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
	if (routesChanged) {
		std::ofstream myfile;
		myfile.open(file.c_str());
		myfile << citynum << std::endl; //write number of cities
		for (int i = 0; i < names.size(); i++) {
			myfile << names[i] << std::endl; //write the names of cities to file
		}
		for (int k = 0; k < citynum; k++) {
			for (int p = k; p < citynum; p++) {
				/*routes are listed with lower number first, by starting at i,
				we avoid listing a route twice, i think */
				if (connections[k][p] == 1) {
					myfile << k + 1 << " " << p + 1 << " " << distances[k][p] << " " << costs[k][p] << ".00" << std::endl;
				}
			}
		}
		myfile.close(); //file is written correctly and closed, rewritten files can be reread
	}

	return 0;
}

void help() {
	std::cout
		<< "************************************\n"
		<< "             HELP MENU               \n"
		<< "Enter 1 to Display Direct Routes\n"
		<< "Enter 2 for Minimum Spanning Tree\n"
		<< "Enter 3 for Shortest Path (based on Miles) point A to Point B\n"
		<< "Enter 4 for Shortest Path (based on Price) point A to Point B\n"
		<< "Enter 5 for Shortest Path (based on Hops) point A to Point B\n"
		<< "Enter 6 for all travel options for given money amount\n"
		<< "Enter 7 to create a new Route between 2 cities\n"
		<< "Enter 8 to delete a Route between 2 cities\n"
		<< "Enter 9 to quit\n"
		<< "*************************************\n";
}

void nameOfCities() {
	std::cout << "Cities Offering Flights:\n";
	for (int j = 0; j < names.size(); j++) {
		std::cout << names[j] << "\n";
	}
	std::cout << "\n";

}


void mst() {}



//helps find minimum weight in shortestPathMiles and shortestPathPrice
int minWeight(std::vector<int> dist, std::vector<bool> visited) {
	// Initialize min value
	int min = INFINITE;
	int min_index;

	for (int v = 0; v < citynum; v++) {
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	}
	return min_index;
}

void shortestPathMiles(int source, int destination) {

	std::vector<int> dist(citynum); //holds minimum distance to each node from source
	std::vector<bool> visited(citynum); //tracks if a vertex is in the path
	std::vector<int> parent(citynum);// Parent array to store shortest path tree
	// prepare vectors as essentially 'empty'
	for (int i = 0; i < citynum; i++) {
		dist[i] = INFINITE; //a huge value, used to help comparisons
		visited[i] = false;
		parent[i] = -1;
	}
	// Distance of source vertex from itself is always 0
	dist[destination] = 0;
	// Find shortest path for all vertices
	for (int count = 0; count < citynum - 1; count++) {
		//find minimum distance of vertices we haven't been to
		int u = minWeight(dist, visited);
		// visited the vertex
		visited[u] = true;
		// Update dist value of the adjacent vertices of the picked vertex

		for (int v = 0; v < citynum; v++)
			/* Update dist[v] only if not visited, there is
		  an edge, and total distance of path from
		   source to v through u is smaller than current value */
			if (!visited[v] && distances[u][v] &&
				dist[u] + distances[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + distances[u][v];
			}
	}
	if (visited[destination] == true && visited[source] == true) { //checks if there is a path from destination to source
		std::cout << "Shortest Path from " << names[source] << " to " << names[destination] << " (Minimum Distance)\n";
		int h = source;
		int totalcost = 0;
		while (h != destination && h != -1) {
			std::cout << names[h] << " -> ($" << costs[h][parent[h]] << ") -> ";
			totalcost += costs[h][parent[h]];
			h = parent[h];
		}
		std::cout << names[destination] << ", total cost = $" << totalcost << ".00\n";
	}
	else
		std::cout << "No Direct Path Avaliable\n";
}


void shortestPathPrice(int source, int destination) {
	std::vector<int> dist(citynum); //holds minimum distance to each node from source
	std::vector<bool> visited(citynum); //tracks if a vertex is in the path
	std::vector<int> parent(citynum);// Parent array to store shortest path tree
	// prepare vectors as essentially 'empty'
	for (int i = 0; i < citynum; i++) {
		dist[i] = INFINITE; //a huge value, used to help comparisons
		visited[i] = false;
		parent[i] = -1;
	}
	// Distance of source vertex from itself is always 0
	dist[destination] = 0;
	// Find shortest path for all vertices
	for (int count = 0; count < citynum - 1; count++) {
		//find minimum distance of vertices we haven't been to
		int u = minWeight(dist, visited);
		// visited the vertex
		visited[u] = true;
		// Update dist value of the adjacent vertices of the picked vertex

		for (int v = 0; v < citynum; v++)
			/* Update dist[v] only if not visited, there is
			an edge, and total distance of path from
			 source to v through u is smaller than current value */
			if (!visited[v] && costs[u][v] &&
				dist[u] + costs[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + costs[u][v];
			}
	}
	if (visited[destination] == true && visited[source] == true) { //checks if there is a path from destination to source
		std::cout << "Shortest Path from " << names[source] << " to " << names[destination] << " (Minimum Distance)\n";
		int h = source;
		int totalcost = 0;
		while (h != destination && h != -1) {
			std::cout << names[h] << " -> ($" << costs[h][parent[h]] << ") -> ";
			totalcost += costs[h][parent[h]];
			h = parent[h];
		}
		std::cout << names[destination] << ", total cost = $" << totalcost << ".00\n";
	}
	else
		std::cout << "No Direct Path Avaliable\n";
}

void shortestPathHops(int source, int destination) {
	bool found = false;
	std::vector<bool> visited(citynum); //track where I've been
	std::vector<int> parents(citynum); //track who I came from to form the path

	for (int i = 0; i < visited.size(); i++)
		visited[i] = false;
	for (int i = 0; i < parents.size(); i++)
		parents[i] = -1;

	if (source == destination) //duh case
		std::cout << "Source and Destination are the same, no travel needed\n";
	else {
		int start = destination; //start at destination so we can work backwards later
		std::queue<int>  Q;
		visited[destination] = true;
		Q.push(start);
		while (!Q.empty()) { //googled BFS and its pretty standard
			int current = Q.front(); //current node
			Q.pop(); //pop it
			for (int i = 0; i < citynum; i++) {
				if (connections[current][i] == 1 && visited[i] == false) {
					visited[i] = true;
					parents[i] = current;

					if (i == source) { //thought this was current, but its actually i we wanna check
						found = true; //error handling in the event that there is no path, works
					}
					else { // push to queue
						Q.push(i);
					}
				}
			}
		}

		if (found) {
			/*print the path, starting from source and following parents[] which works like a pointer
			a little shifty, should probably have a check to see if 2 nodes are connected at all.
			the domestic file is 100% connected, so no chance of issues there. */
			std::cout << "Shortest Path from " << names[source] << " to " << names[destination] << "\n";
			int h = source;
			int totalcost = 0;
			while (h != destination) {
				std::cout << names[h] << " -> ($" << costs[h][parents[h]] << ".00) -> ";
				totalcost += costs[h][parents[h]];
				h = parents[h];
			}
			std::cout << names[destination] << ", 	total cost = $" << totalcost << ".00\n";
		}
		else //no path
			std::cout << "No path found between entered cities\n";
	}
}


//needs implemented
void tripPriceOptions(int source, double price) {}

void newRoute(int source, int destination, double cost, double distance) {
	if (connections[source][destination] == 1) {
		std::cout << "Error: there is already a route here!\n";
	}
	else {
		connections[source][destination] = 1;
		connections[destination][source] = 1;
		costs[source][destination] = cost;
		costs[source][destination] = cost;
		distances[source][destination] = distance;
		distances[destination][source] = distance;
	}

}

void deleteRoute(int source, int destination) {
	if (connections[source][destination] == 0) {
		std::cout << "Error: there is no route here to remove\n";
	}
	else {
		connections[source][destination] = 0;
		connections[destination][source] = 0;
		costs[source][destination] = -1;
		costs[source][destination] = -1;
		distances[source][destination] = -1;
		distances[destination][source] = -1;
	}

}

void directRoutes() {
	int maxLen = 0;
	for (std::string s : names) {
		maxLen = s.length() > maxLen ? s.length() : maxLen;
	}
	for (int i = 0; i < names.size(); i++)
	{
		for (unsigned int j = 0; j < names.size(); j++)
		{
			if (connections[i][j] == 1) {
				std::cout << std::setw(maxLen) << std::left
					<< names[i];
				std::cout << " -> " << std::setw(maxLen) << std::left
					<< names[j] << '\t';
				std::cout << "$" << distances[i][j] << '\t'
					<< costs[i][j] << " mi\n";
			}
		}
	}
}

int getCity(std::string prompt) {
	std::string cityName;
	bool error = true;
	while (error) {
		std::cout << prompt;
		std::cin >> cityName;
		for (int i = 0; i < names.size(); i++)
		{
			if (names[i] == cityName) {
				return i;
			}
		}
		std::cout << cityName << " does not exist!\n\n";
	}
	return -1;
}
