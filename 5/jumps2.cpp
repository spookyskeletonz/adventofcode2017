#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main(int argc, char **argv){
    std::ifstream filein(argv[1]);
    int countpos = 0;
    int currentjump;
    std::string scurrentjump;
    std::unordered_map<int, int> jumps;
    
    while(std::getline(filein, scurrentjump)){
        currentjump = std::stoi(scurrentjump);
        jumps.insert(std::make_pair(countpos, currentjump));
        countpos++;
    }
    
    int pos = 0;
    int steps = 0;
    while(pos < countpos && pos >= 0){
        int jump = jumps[pos];
        int newpos = pos + jump;
        jumps[pos] < 3? jumps[pos]++ : jumps[pos]--;
        steps++;
        pos = newpos;
    }
    std::cout << "escaped in " << steps << " steps\n";


}
