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
       for(int i : intLine){
           for(int k : intLine){
               if(i%k == 0 && i != k){
                   checksum += i/k;
               }
           }
       }
   }
   std::cout << checksum << "\n";
}
