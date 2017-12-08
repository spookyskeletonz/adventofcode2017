#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <regex>

struct Node{
    std::string name;
    std::string parent;
    int weight;
    std::vector<std::string> children;
};

std::unordered_map<std::string, Node> nameToNodeMap;

void createOrEditNode(std::string, int, std::vector<std::string>);
void createOrEditChildNodes(std::string, std::vector<std::string>);
std::string findBase();

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

        createOrEditNode(name, weight, childs);
        createOrEditChildNodes(name, childs);
        
   }

    //now we have constructed tree time to find base node
   std::cout << "base: " << findBase() << "\n";
}

std::string findBase(){
    std::string base;
    Node current;
    for(auto it : nameToNodeMap){
        current = it.second;
        if(current.parent == ""){
            base = current.name; 
        }
    }
    return base; 
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
