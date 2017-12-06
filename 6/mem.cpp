#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char **argv){
  std::unordered_set<std::string> states;
  std::ifstream infile(argv[1]);
  std::string line;
  std::vector<int> banks;
  while(std::getline(infile, line)){
    std::istringstream iss(line);
    int b;
    while(iss >> b){
      banks.push_back(b);
    }
  }
  std::string initialstate;
  for(int i : banks){
    initialstate += "|"+ std::to_string(i);
  }
  states.insert(initialstate);
  
  bool escapeflag = false;
  int steps = 0;
  while(!escapeflag){
    int holdingblocks = 0;
    //get max first
    int maxpos = 0;
    for(int currentpos = 0; currentpos < banks.size(); ++currentpos){
      if(banks[currentpos] > holdingblocks){
        holdingblocks = banks[currentpos];
        maxpos = currentpos;
      }
    }
    banks[maxpos] = 0;
    int currentpos = maxpos+1;
    //now distribute blocks
    while(holdingblocks > 0){
      if(currentpos == banks.size()) currentpos = 0;
      banks[currentpos]++;
      holdingblocks--;
      currentpos++;
    }
    steps++;
    //now convert to state strign and then check state hasnt been seen. if it has escape
    std::string state;
    for(int i : banks){
      state += "|" + std::to_string(i);
    }
    if(states.find(state) != states.end()) escapeflag = true;
    else states.insert(state);
  }

  std::cout << "it took " << steps << " steps to reach duplicate state" << "\n";
}
