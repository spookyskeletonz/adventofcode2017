#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv){
    std::ifstream infile(argv[1]);
    bool garbageFlag = false;
    bool ignoreFlag = false;
    int score = 0;
    int currentDepth = 0;
    int openBrackets = 0;
    
    char c;
    while(infile.get(c)){
        if(!ignoreFlag){
            if(!garbageFlag){
                if(c == '{'){
                    currentDepth++;
                    openBrackets++;
                } else if(c == '}' && openBrackets != 0){
                     openBrackets--;
                     score += currentDepth;
                     currentDepth--;

                }
            }
            if(c == '!'){
                ignoreFlag = true;
            } else if(c == '<'){
                garbageFlag = true;
            } else if(c == '>'){
                garbageFlag = false;
            }
        
        
        } else {
            ignoreFlag = false;
        }
    }

    std::cout << "score: " << score << "\n";
}
