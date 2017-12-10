#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv){
    std::ifstream infile(argv[1]);
    bool garbageFlag = false;
    bool ignoreFlag = false;
    int count = 0; 
    char c;
    while(infile.get(c)){
        if(!ignoreFlag){
            if(garbageFlag){
                count++;
            }
            if(c == '!'){
                count--;
                ignoreFlag = true;
            } else if(c == '<'){
                garbageFlag = true;
            } else if(c == '>'){
                count--;
                garbageFlag = false;
            }
        
        
        } else {
            ignoreFlag = false;
        }
    }

    std::cout << "count: " << count << "\n";
}
