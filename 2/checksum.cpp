#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>
    
int main(int argc, char **argv){
   std::ifstream infile(argv[1]); 
   std::string line;
   int checksum = 0;
   while(std::getline(infile, line)){
       std::istringstream iss(line);         
       int tmp;
       std::vector<int> intLine;
       while(iss >> tmp){
           intLine.push_back(tmp);
       }
       int hi = INT_MIN;
       int lo = INT_MAX;
       for(int i : intLine){
           if(i < lo) lo = i;
           if(i > hi) hi = i;
       }
       checksum += hi - lo;
   }
   std::cout << checksum << "\n";
}
