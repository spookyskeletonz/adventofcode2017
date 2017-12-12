#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int x = 0; /*  axis: / */
int y = 0; /* axis: \ */
int z = 0; /* axis - */

void newStep(std::string);

int main(int argc, char **argv){
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile, line);
    std::string token;
    size_t pos = 0;

    while((pos = line.find(',')) != std::string::npos){
        token = line.substr(0, pos);
        newStep(token);
        line.erase(0, pos + 1);
    }
    newStep(line); 
    std::cout << std::max({std::abs(0-x), std::abs(0-y), std::abs(0-z)}) << "\n";
}

void newStep(std::string direction){
    if(direction == "s"){
        x--;
        y--;
    } else if(direction == "se"){
        z++;
        y--;
    } else if(direction == "ne"){
        x++;
        z++;
    } else if(direction == "n"){
        x++;
        y++;
    } else if(direction == "nw"){
        y++;
        z--;
    } else if(direction == "sw"){
        z--;
        x--;
    }
}

