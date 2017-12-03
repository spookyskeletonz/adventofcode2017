#include <map>
#include <cstdlib>
#include <iostream>
#include <utility>

int main(){
    int lastpoint = 312051;
    int x = 0;
    int y = 0;
    bool left = true;
    bool right = false;
    bool up = false;
    bool down = false;
    std::map<std::pair<int, int>, int> g;
    g[std::make_pair(x, y)] =  1;
    x++;
    g[std::make_pair(x, y)] =  2;
    y++;
    for(int i = 3; i <= lastpoint; ++i){
       if(i == lastpoint){
           std::cout << " x: " << x << " y: " << y << " manhattan dist: " << std::abs(x) + std::abs(y) << "\n";
       }
       if(up){
           g[std::make_pair(x, y)] = i;
           if(g.find(std::make_pair(x-1, y)) == g.end()){
               up = false;
               left = true;
               x--;
           } else {
               y++;
           }
       } else if(left){
           g[std::make_pair(x, y)]  = i;
           if(g.find(std::make_pair(x, y-1)) == g.end()){
               left = false;
               down = true;
               y--;
           } else {
               x--;  
           }
       } else if(down){
           g[std::make_pair(x, y)] = i;
           if(g.find(std::make_pair(x+1, y)) == g.end()){
               down = false;
               right = true;
               x++;
           } else {
               y--;
           }
       } else if(right){
           g[std::make_pair(x, y)] = i;
           if(g.find(std::make_pair(x, y+1)) == g.end()){
               right = false;
               up = true;
               y++;
           } else {
               x++;
           }
       } else{
           std::cout << "no direction set\n"; 
       }
    }
}

