#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

bool isConditionalMet(std::string, std::string, int);
void incrementOrDecrement(std::string, std::string, int);

std::unordered_map<std::string, int> registers;

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    std::string line;
    while(std::getline(infile, line)){
        //load data into variables
        std::istringstream iss(line);
        std::string registerName;
        std::string operation;
        int value;
        std::string conditionalRegister1;
        std::string conditionalOperator;
        int value2;
        
        std::string word;
        int count = 0;
        while(iss >> word){
            if(count == 0) registerName = word;
            if(count == 1) operation = word;
            if(count == 2) value = std::stoi(word);
            if(count == 4) conditionalRegister1 = word;
            if(count == 5) conditionalOperator = word;
            if(count == 6) value2 = std::stoi(word);
            ++count;
        }

        //initialise mentioned registers if not set
        if(registers.find(registerName) == registers.end()) registers.insert(std::make_pair(registerName, 0));
        if(registers.find(conditionalRegister1) == registers.end()) registers.insert(std::make_pair(conditionalRegister1, 0));

        if(isConditionalMet(conditionalRegister1, conditionalOperator, value2)){
            incrementOrDecrement(registerName, operation, value);
        }

    }
    int maxVal = 0;
    for(auto i : registers){
        if(i.second > maxVal) maxVal = i.second;
    }
    std::cout << maxVal << "\n";


    
}

bool isConditionalMet(std::string r1, std::string o, int v){
    if(o == "<") return registers[r1] < v;
    else if(o == ">") return registers[r1] > v;
    else if(o == "==") return registers[r1] == v;
    else if(o == "!=") return registers[r1] != v;
    else if(o == "<=") return registers[r1] <= v;
    else if(o == ">=") return registers[r1] >= v;
    else std::cout << "invalid conditional: " << o << "\n";

    return false;

}

void incrementOrDecrement(std::string r, std::string o, int v){
    if(o == "inc") registers[r] += v;
    else if(o == "dec") registers[r] -= v;
    else std::cout << "invalid increment/decrement: " << o << "\n";
}
