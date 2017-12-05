#include <iostream>
#include <vector>
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
    std::string word;
    std::unordered_set<std::string> words;
    bool isPhrase = true;
    while(iss >> word){
      std::vector<int> wordVec(26);
      for(int i = 0; i < word.length(); ++i){
        wordVec[word[i]-97]++;
      }
      std::string s;
      for(int i : wordVec)
        s = s + std::to_string(i);
      if(words.find(s) != words.end()){
        isPhrase = false;
      }
      else words.insert(s);
    }
    if(isPhrase) count++;
  }
  std::cout << "number of valid passphrases: " << count << "\n";
}


