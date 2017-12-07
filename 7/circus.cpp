#include<set>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <regex>

struct Node{
    std::string name;
    std::string parent = "";
    int weight;
    std::set<std::string> children;
};

std::unordered_map<std::string, Node*> nameToNodeMap;
std::set<Node> nodes;

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
        std::regex c("^.*->");
        std::set<std::string> childs;
        if(std::regex_search(line, c)){
            std::string children = std::regex_replace(line, c , "");
            std::string delimiter = ", ";
            size_t pos = 0;
            std::string token;
            while((pos = children.find(delimiter)) != std::string::npos){
                token = children.substr(0, pos);
                childs.insert(token);
                children.erase(0, pos + delimiter.length());
            }
        }
        
        //create or edit node
        if(nameToNodeMap.find(name) != nameToNodeMap.end()){
            Node *node = nameToNodeMap[name];
            node->weight = weight;
            node->children = childs;
        } else {
            Node *newNode = new Node;
            newNode->name = name;
            newNode->weight = weight;
            newNode->children = childs;
            nodes.insert(newNode);
            nameToNodeMap.insert(std::make_pair(name, newNode));
        }

        //create childs if not exist or edit if do exist
        for(std::string child : childs){
            if(nameToNodeMap.find(child) != nameToNodeMap.end()){
                Node *node = nameToNodeMap[child];
                node->parent = name;
            } else {
                Node *newNode = new Node;
                newNode->name = child;
                newNode->parent = name; 
                nodes.insert(newNode);
                nameToNodeMap.insert(std::make_pair(child, newNode));
            }
        }

    }

    //now we have constructed tree time to find base node
    Node *base;
    for(Node *current : nodes){
        if(current.parent = "") base = current;
    }
    std::cout << base->name << "\n";
}
