#include<set>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <regex>

struct node{
    std::string parent;
    int weight;
    std::set<std::string> children;
};

std::unordered_map<std::string, node> nameToNodeMap;
std::set<node> nodes;

int main(int argc, char **argv){
    std::ifstream infile(argv[1]);
    std::string line;
    while(std::getline(infile, line)){
        std::regex r(" .*$");
        std::string name = std::regex_replace(line, r, "");
        std::string sweight = std::regex_replace(line, "^.*\(", "");
        sweight = std::regex_replace(sweight, "\).*$", "");
        std::istringstream isweight(sweight);
        int weight << isweight;
        std::string children = std::regex_replace(line, "^.*-> ", "");
        std::cout << name << "   " << weight << "   " << children << "\n";
    }
}
