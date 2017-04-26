//Clay Wyers Jared Ford final Proj

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>


int main(int argc, char *argv[]) {

	std::string file = argv[1]; //the file name

	int citynum; //first line of file

	std::vector<std::string> names; //for sure
	std::vector<std::vector<int> > connections;
	std::vector<std::vector<int> > costs;
	std::vector<std::vector<int> > distances;
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
	//std::cout << stringvalues << "\n\n\n" << std::endl;
	  //fill array with numbers in string
	//  int values[width][height];
	/*
	  int currentspace = 0; //current spot on string, starting point for next number
	  int nextspace; // location of next space, which seperates the numbers
		for (int h = 0; h < height; h++){
		for (int w = 0; w < width; w++){
			int nextspace = stringvalues.find(" ", currentspace); //fill array with stringvalues
			values[w][h] = std::stoi(stringvalues.substr(currentspace, currentspace - nextspace));
			currentspace = nextspace + 1;
		}
		}

	//print values to ensure they were read correctly
	for (int h = 0; h < height; h++){
		for (int w = 0; w < width; w++){
			std::cout << values[w][h] << " ";
		}
		std::cout << std::endl;
	}

	  //this is a useful reference to make sure everything was read correctly
	  std::cout << "s contains: " << s << std::endl;
	  std::cout << "comment contains: " << comment << std::endl;
	  std::cout << "width = " << width << std::endl;
	  std::cout << "height = " << height << std::endl;
	  std::cout << "IMAGE HAS BEEN PROCESSED" << std::endl;
		std::string processedstring = "";
		for (int h = 0; h < height; h++){
		  for (int w = 0; w < width; w++){
					if (values[w][h] != -1)
					processedstring += std::to_string(values[w][h]) + " ";
			//std::cout << values[w][h] << " ";
		  }
				processedstring += "\n";
				//std::cout << std::endl;
		}
			//recalculate dimensions with new width and height, so that they are written to file correctly
			dimensions = std::to_string(width) + " " + std::to_string(height);
			//combine all strings back together to write to the file
			s += "\n" + comment + "\n" + dimensions + "\n" + maxcolor + "\n" + processedstring;

		//export file here
	  int stringsize = file.size()- 4;
	  std::string filenam = file.substr(0,stringsize);
	  filenam += "_processed.pgm";
	  const char * processed = s.c_str();
	  std::streampos fsize =  s.size();
	  std::ofstream myfile9 (filenam.c_str());
	  myfile9.write (processed,fsize);
	  myfile9.close();
	*/
	return 0;
}
