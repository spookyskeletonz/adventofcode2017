#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char** argv){
    std::string filename = argv[1];
    char ch;
    std::fstream fin(filename, std::fstream::in);
    std::vector<char> characters;
    while (fin  >> ch) {
        characters.push_back(ch);
    }
    int runningsum = 0;
    for(int count = 0; count < characters.size(); ++count){
        int checkone = characters.at(count)-48;
        int match = count + characters.size()/2;
        if(match >= characters.size()){
            match = match - characters.size(); 
        }
        int checktwo = characters.at(match)-48;
        if(checkone == checktwo){
            runningsum = runningsum + checkone;
        }
    }
    std::cout << runningsum << "\n";
}
