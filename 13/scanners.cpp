#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    std::string line;
    int severity = 0;
    while(std::getline(infile, line)){
      std::istringstream iss(line);
      std::string sdepth;
      iss >> sdepth;
      sdepth.erase(std::remove(sdepth.begin(), sdepth.end(), ','), sdepth.end());
      int depth = std::stoi(sdepth);
      std::string srange;
      iss >> srange;
      int range = std::stoi(srange);
      if(depth%((range-1)*2) == 0) severity += depth*range;
    }

    std::cout << "severity: " << severity << "\n";
}
