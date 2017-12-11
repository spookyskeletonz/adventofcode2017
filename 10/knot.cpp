#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile, line);
    std::string token;
    std::vector<int> list;
    std::vector<int> input;
    //create vector of 0-255
    for(int i = 0; i < 256; ++i){
        list.push_back(i);
    }
    //load inputs into other vector for future use
    size_t pos = 0;
    while((pos = line.find(',')) != std::string::npos){
        token = line.substr(0, pos);
        input.push_back(std::stoi(token));
        line.erase(0, pos + 1);
    } 
    input.push_back(std::stoi(line));

    int skipSize = 0;
    int currentPos = 0;
    for(int i = 0; i < input.size(); ++i){
        auto it = list.begin() + currentPos;
        std::vector<int> subVec;
        int length = input[i];
        for(int k = 0; k < length; ++k){
            subVec.push_back(*it);
            it++;
            if(it == list.end()) it = list.begin();
        }
        std::reverse(subVec.begin(), subVec.end());
        int pos = currentPos;
        for(int k = 0; k < length; ++k){
            list[pos] = subVec[k];
            pos++;
            if(pos == list.size()) pos = 0;
        }
        currentPos += length + skipSize;
        if(currentPos >= list.size()) currentPos = currentPos - list.size();
        skipSize++;
    }

    std::cout << "result: " << list[0] * list[1] << "\n";

}

