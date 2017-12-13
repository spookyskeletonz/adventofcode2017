#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv){
  int delayCounter = 0;
  while(true){
      std::ifstream infile(argv[1]);
      std::string line;
      bool escape = false;
      while(std::getline(infile, line)){
          std::istringstream iss(line);
          std::string sdepth;
          iss >> sdepth;
          sdepth.erase(std::remove(sdepth.begin(), sdepth.end(), ','), sdepth.end());
          int depth = std::stoi(sdepth);
          std::string srange;
          iss >> srange;
          int range = std::stoi(srange);
          if((delayCounter+depth)%((range-1)*2) == 0){
              escape = true;
              break;
          }
      }
      if(escape == true){
          delayCounter++;
          continue;
      } else {
          break;
      }
  }

    std::cout << "delay: " << delayCounter << "\n";
}
