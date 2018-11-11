/*
  Author: John Genere

  Test done individually (per case) so that there is no effect on duration time
  per test.
*/
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "trees.h"

int main(){
  AVL <int> test;         // change per test

  std::vector<int> v;
  srand((unsigned)time(0));
  int randomInteger;
  int range = 1000000;    // change per test

  // randomly inserts numbers starting from 1 - range to vector
  for(int i = 0; i < range; i++){
    randomInteger = rand();
    v.push_back(randomInteger);
  }

  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  // insertion while avoiding duplicates if any
  for(int i = 0; i < v.size(); i++){
    test.insert(v[i]);
  }

  // removal of item if in the tree
  for(int i = 0; i < v.size(); i += 2){
    test.remove(v[i]);
  }

  auto t2 = std::chrono::steady_clock::now();

  std::cout << "Duration is " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << std::endl;
}
