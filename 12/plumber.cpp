#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>

struct Node{
    int label;
    std::set<Node*> neighbours;
    Node(int l) : label(l) {}
};

int groupCount = 0;
std::map<int, Node*> nodeMap;
std::set<Node*> visited;

void traverseAndCount(Node*);
void addNode(const int&);
void addEdge(const int&, const int&);

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    std::string line;
    while(std::getline(infile, line)){
        std::istringstream iss(line);
        std::string word;
        iss >> word;
        addNode(std::stoi(word));
        Node *one = nodeMap.find(std::stoi(word))->second;
        while(iss >> word){
            if(word == "<->") continue;
            word.erase(std::remove(word.begin(), word.end(), ','), word.end());
            addNode(std::stoi(word));
            Node *neighbour = nodeMap.find(std::stoi(word))->second;
            one->neighbours.insert(neighbour);
            if(neighbour->neighbours.find(one) != neighbour->neighbours.end()) neighbour->neighbours.insert(one);
        }
    }

    Node *base = nodeMap.find(0)->second;
    visited.clear();
    traverseAndCount(base);
    std::cout << "number of nodes that can reach 0: " << groupCount << "\n";
}

void traverseAndCount(Node* current){
    visited.insert(current);
    groupCount++;
    for(Node* neighbour : current->neighbours){
        if(visited.find(neighbour) == visited.end()) traverseAndCount(neighbour);
    }
}

void addNode(const int& label){
    auto it = nodeMap.find(label);
    if(it != nodeMap.end()){
        return;
    }

    Node *n;
    n = new Node(label);
    nodeMap[label] = n;
    return;
}

void addEdge(const int& from, const int& to){
    Node *one = nodeMap.find(from)->second;
    Node *two = nodeMap.find(to)->second;
    one->neighbours.insert(two);
    two->neighbours.insert(one);
}
