//Clay Wyers Jared Ford final Proj

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>


int main(int argc, char *argv[]){

	std::string file = argv[1]; //the file name

  int citynum = 10; //first line of file

	std::vector<std::string> names; //for sure
	std::vector<std::vector<int> > connections(citynum, std::vector<int>(citynum));
	std::vector<std::vector<int> > costs(citynum, std::vector<int>(citynum));
	std::vector<std::vector<int> > distances(citynum, std::vector<int>(citynum));

for (int i = 0; i < 10; i++){
	for (int j = 0; j< 10; j++){
		connections[i][j] = 9999;
	}
}


for (int i = 0; i < 10; i++){
	for (int j = 0; j< 10; j++){
		std::cout << connections[i][j] << " ";
	}
	std::cout << "\n";
}

  //some of the needed variables
  std::ifstream myfile2;

  std::string currentline;
  std::string stringvalues;

  myfile2.open (file.c_str());
	std::string citynumberstring;
	std::string cityname;
  getline(myfile2,citynumberstring);
	citynum = std::stoi(citynumberstring);
	std::cout << "citynum = " << citynum << "\n";
	for (int k = 0; k < citynum; k++){
	getline(myfile2, cityname);
	std::cout << cityname << "\n";
	names.push_back(cityname);
	//names[k].push_back(cityname);
	//std::cout << names.at(k) << " ";
}

/*
  getline(myfile2, dimensions);
  int seperator = dimensions.find(" "); //only looks for spaces, no tab support
  int width = std::stoi(dimensions.substr(0, seperator));
  int height = std::stoi(dimensions.substr(seperator));
  getline(myfile2, maxcolor);

  while (!myfile2.eof()){ //get all values, save to a string
    getline(myfile2, currentline);
    stringvalues += currentline; }*/

  myfile2.close();
std::cout << "NAMES SIZE = " << names.size() << std::endl;
	for (int j = 0; j < names.size(); j++){
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
