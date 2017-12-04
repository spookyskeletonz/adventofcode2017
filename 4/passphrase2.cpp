#include <iostream>
#include <vector>
#include <map>
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
    std::map<std::vector<int>, int> words;
    bool isPhrase = true;
    while(iss >> word){
      std::vector<int> wordVec(26);
      for(int i = 0; i < word.length(); ++i){
        wordVec[word[i]-97]++;
      }
      if(words.find(wordVec) != words.end()){
        isPhrase = false;
      }
      else words.insert(std::make_pair(wordVec, 1));
    }
    if(isPhrase) count++;
  }
  std::cout << "number of valid passphrases: " << count << "\n";
}


