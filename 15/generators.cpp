#include <iostream>
#include <string>
#include <sstream>

void binary(std::stringstream&, long);
void trim(std::string&, int);

int main(int argc, char **argv){
  long a = 289;
  long b = 629;
  long  matches = 0;
  for(long count = 0; count < 40000000; count++) {
    
    a = (a * 16807)%2147483647;
    b = (b * 48271)%2147483647;
    std::stringstream ass;
    binary(ass, a);
    std::string as = ass.str();
    trim(as,16);
    std::stringstream bss;
    binary(bss, b);
    std::string bs = bss.str();
    trim(bs, 16);
    if(as == bs) matches++;
    if(count == 1000000) std::cout << "calculated 1000000 pairs";
    else if(count == 5000000) std::cout << "calculated 5000000 pairs";
    else if(count == 20000000) std::cout << "calculated 20000000 pairs";
    else if(count == 30000000) std::cout << "calculated 30000000 pairs";
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
