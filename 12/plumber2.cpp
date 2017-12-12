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

int groupsCount = 0;
std::map<int, Node*> nodeMap;
std::set<Node*> visited;
std::set<Node*> unvisited;

void traverse(Node*);
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

    visited.clear();
    for(auto p : nodeMap){
        unvisited.insert(p.second);
    }
    while(!unvisited.empty()){
        //logic is we clear nodes as we explore them from the unvisited
        //every time we finish traversing, we have fully traversed a group, and
        //all those nodes have been cleared from unvisited
        traverse(*unvisited.begin());
        groupsCount++;
    }
    std::cout << "number of groups: " << groupsCount << "\n";
}

void traverse(Node* current){
    //traverses through neighbours recursively. removes from unvisited nodes,
    //adds to visited.
    visited.insert(current);
    unvisited.erase(current);
    for(Node* neighbour : current->neighbours){
        if(visited.find(neighbour) == visited.end()) traverse(neighbour);
    }
}

void addNode(const int& label){
    //creates a new node if it doesnt already exist
    //adds it to nodeMap
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
    //takes two ints as input. finds the corresponding nodes and links them together
    //by adding each other as neighbours
    Node *one = nodeMap.find(from)->second;
    Node *two = nodeMap.find(to)->second;
    one->neighbours.insert(two);
    two->neighbours.insert(one);
}
