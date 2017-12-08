#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

struct Node{
    int totalWeight;
    std::string name;
    std::string parent;
    int weight;
    std::vector<std::string> children;
};

std::unordered_map<std::string, Node> nameToNodeMap;

void createOrEditNode(std::string, int, std::vector<std::string>);
void createOrEditChildNodes(std::string, std::vector<std::string>);
std::string findBase();
int populateTotalWeights(std::string);
int findImbalance(std::string, int);

int main(int argc, char **argv){
    std::ifstream infile(argv[1]);
    std::string line;
    while(std::getline(infile, line)){
        //clean data into variables to init nodes
        std::regex n(" .*$");
        std::string name = std::regex_replace(line, n, "");
        std::regex s("^.*\\(");
        std::string sweight = std::regex_replace(line, s, "");
        std::regex s2("\\).*$");
        sweight = std::regex_replace(sweight, s2, "");
        int weight = std::stoi(sweight);
        std::regex c("^.*-> ");
        std::vector<std::string> childs;
        if(std::regex_search(line, c)){
            std::string children = std::regex_replace(line, c , "");
            std::string delimiter = ", ";
            size_t pos = 0;
            std::string token;
            while((pos = children.find(delimiter)) != std::string::npos){
                token = children.substr(0, pos);
                childs.push_back(token);
                children.erase(0, pos + delimiter.length());
            }
            //last token left over cant be bothered to format it more lol
            childs.push_back(children);
        }

        //create/edit nodes and childs for this line
        createOrEditNode(name, weight, childs);
        createOrEditChildNodes(name, childs);
        
    }    

    std::string base = findBase();
    //now we have constructed all nodes time to find base node
    std::cout << "base: " << base << "\n";

    //now we will populate all the totalWeights at each plate. the total weight is the sum of the plate plus the plates above
    std::cout << "total weight of all plates: " << populateTotalWeights(base);

    //now we have to find the imbalanced plate and get the value it should be
}

std::string findBase(){
    Node current;
    for(auto it : nameToNodeMap){
        if(it.second.parent == ""){
            return it.second.name; 
        }
    }
    return ""; 
}

void createOrEditNode(std::string name, int weight, std::vector<std::string> childs){
    //create or edit node
    if(nameToNodeMap.find(name) != nameToNodeMap.end()){
        Node *node = &nameToNodeMap[name];
        node->weight = weight;
        node->children = childs;
    } else {
        Node newNode;
        newNode.name = name;
        newNode.weight = weight;
        newNode.children = childs;
        nameToNodeMap.insert(std::make_pair(name, newNode));
    }
}

void createOrEditChildNodes(std::string name, std::vector<std::string> childs){
    //create childs if not exist or edit if do exist
    for(std::string child : childs){
        if(nameToNodeMap.find(child) != nameToNodeMap.end()){
            nameToNodeMap[child].parent = name;
        } else {
            Node newNode;
            newNode.name = child;
            newNode.parent = name; 
            nameToNodeMap.insert(std::make_pair(child, newNode));
        }
    }
}

int populateTotalWeights(std::string current){
    int totalWeight = nameToNodeMap[current].weight;
    for(std::string child : nameToNodeMap[current].children){
        totalWeight += populateTotalWeights(child);
    }
    nameToNodeMap[current].totalWeight = totalWeight;
    return totalWeight;
}

int findImbalance(std::string current, int expectedWeight){
    //todo: implement case for 2 that are unequal
    if(nameToNodeMap[current].children.size() > 2){
        int first = nameToNodeMap[current].children[0].totalWeight;
        int temp = first;
        for(std::string child : nameToNodeMap[current].children){
            if(nameToNodeMap[child].totalWeight != first && child = nameToNodeMap[current].children[1]) temp = nameToNodeMap[child].totalWeight; 
            else if(nameToNodeMap[child].totalWeight != first && nameToNodeMap[child].totalWeight == temp)
                return findImbalance(nameToNodeMap[current].children[0].name, temp)
            else if(nameToNodeMap[child].totalWeight == first && nameToNodeMap[child].totalWeight != temp)
                return findImbalance(nameToNodeMap[current].children[1].name, first);
            else if(nameToNodeMap[child].totalWeight != first && nameToNodeMap[child].totalWeight != temp)
                return findImbalance(child, first);
        }
    } else if(nameToNodeMap[current].children.size() == 2){
        
    }
    return std::abs(nameToNodeMap[current].totalWeight - expectedWeight);
}

