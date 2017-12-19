#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

void binary(std::stringstream&, long);
void trim(std::string&, int);

int main(int argc, char **argv){
  long a = 289;
  long b = 629;
  std::unordered_map<long,std::string> aVals;
  std::unordered_map<long,std::string> bVals;
  long aCount = 0;
  long bCount = 0;
  long matches = 0;

  while(aCount < 5000000 || bCount < 5000000){
  
    a = (a * 16807)%2147483647;
    if(a%4 == 0){
      //if there is a b value for the current a position and they  match, we increment matches.
      //regardless of if there is a match or not, if there is a b value for that position we remove it after this check
      //to save space
      //if there is no b value for that position yet we store the position and a value for future use by b check
      //we then increment aCount.
      std::stringstream ass;
      binary(ass, a);
      std::string as = ass.str();
      trim(as,16);
      if(bVals.find(aCount) != bVals.end()){
        if(as == bVals[aCount]){
          matches++;
        }
        bVals.erase(aCount);
      } else {
        aVals.insert(std::make_pair(aCount, as));
      }
      aCount++;
    }

    //same logic as above but flipped
    b = (b * 48271)%2147483647;
    if(b%8 == 0){
      std::stringstream bss;
      binary(bss, b);
      std::string bs = bss.str();
      trim(bs, 16);  
      if(aVals.find(bCount) != aVals.end()){
        if(bs == aVals[bCount]){
          matches++;
        }
        aVals.erase(bCount);
      } else {
        bVals.insert(std::make_pair(bCount, bs));
      }
      bCount++;
    }
    
  }
  std::cout << "there are " << matches << "matches\n";
}


void binary(std::stringstream& out, long number) {
  int remainder;
  if(number <= 1) {
          out << number;
          return;
  }
  remainder = number%2;
  binary(out, number >> 1);
  out << remainder;
}


void trim(std::string& input, int n) {
  if(input.size() >= n){
    input = input.substr(input.size()-n);
  }
}
