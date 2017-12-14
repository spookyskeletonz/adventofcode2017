#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <bitset>
#include <map>
#include <set>

std::map<std::pair<int,int>,char> bitmap;
std::set<std::pair<int,int>> unvisitedUsed;

std::string knothash(std::string);
void findRegion(int, int);

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile, line);
    std::string rowKey;
    for(int i = 0; i < 128; ++i){
        rowKey = line + "-" + std::to_string(i);
        std::string hexrep = knothash(rowKey);
        std::string row;
        int colCount = 0;
        for(char c : hexrep){
            std::stringstream ss;
            ss << std::hex << c;
            unsigned n;
            ss >> n;
            std::bitset<4> b(n);
            std::string bs = b.to_string();
            for(char c : bs){
                bitmap.insert(std::make_pair(std::make_pair(colCount, i), c));
                if(c == '1') unvisitedUsed.insert(std::make_pair(colCount, i));
                colCount++;
            }
            row += bs;
        }
    }
    int totalCount = 0;
    while(!unvisitedUsed.empty()){
        findRegion(unvisitedUsed.begin()->first, unvisitedUsed.begin()->second);
        totalCount++;
    }
    std::cout << "total number of regions: " << totalCount << "\n";
}

void findRegion(int x, int y){
    unvisitedUsed.erase(std::make_pair(x,y));
    if(unvisitedUsed.find(std::make_pair(x+1,y)) != unvisitedUsed.end()){
        findRegion(x+1,y);
    } 
    if(unvisitedUsed.find(std::make_pair(x-1,y)) != unvisitedUsed.end()){
        findRegion(x-1, y);
    } 
    if(unvisitedUsed.find(std::make_pair(x,y+1)) != unvisitedUsed.end()){
        findRegion(x, y+1);
    } 
    if(unvisitedUsed.find(std::make_pair(x,y-1)) != unvisitedUsed.end()){
        findRegion(x, y-1);
    }
}


std::string knothash(std::string line){
    std::vector<int> list;
    std::vector<int> input;
    //create vector of 0-255
    for(int i = 0; i < 256; ++i){
        list.push_back(i);
    }
    //load inputs into other vector for future use
    for(char c : line){
        input.push_back(static_cast<int>(c));
    }
    input.push_back(17);
    input.push_back(31);
    input.push_back(73);
    input.push_back(47);
    input.push_back(23);

    int skipSize = 0;
    int currentPos = 0;

    for(int j = 0; j < 64; ++j){
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
            if(currentPos >= list.size()) currentPos = currentPos % list.size();
            skipSize++;
        }
    }
    std::vector<int> dense;
    for(int i = 0; i < 16; ++i){
        int count = i*16;
        int res = list[count];
        count++;
        while(count != (i+1)*16){
            res = res ^ list[count];
            count++;
        }
        dense.push_back(res);
    }
    std::string hexrep;
    for(int i = 0; i < dense.size(); ++i){
        std::stringstream n;
        n << std::hex << dense[i];
        std::string res;
        n >> res;
        if(res.size() == 1) res = "0"+res;
        hexrep += res;
    }
    return hexrep;
}

