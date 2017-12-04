#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char **argv){
  std::ifstream infile(argv[1]);
  std::string line;
  int count = 0;
  while(std::getline(infile, line)){
    std::istringstream iss(line);
    std::unordered_set<std::string> words;
    std::string word;
    bool isPhrase = true;
    while(iss >> word){
      if(words.find(word) != words.end()) isPhrase = false;
      else words.insert(word);
    }
    if(isPhrase) count++;
  }
  std::cout << "number of valid passphrases: " << count << "\n";
}
