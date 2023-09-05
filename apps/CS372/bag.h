#pragma once
#include <iostream>
#include "list.h"

template <typename Thing>
class Bag {
public:
  void insert(Thing aThing) {
    bagContents.push_back(aThing);
  }
  
  Thing pop() {
    if (empty()) {
      std::cerr << "Can't pop out of an empty bag" << std::endl;
      return Thing();
    }
    
    Thing aThing = bagContents.back();
    bagContents.pop_back();
    return aThing;
  }

  int size() const {
    return bagContents.size();
  }

  int count(Thing aThing) const {
    int bagCount = 0;
    for (const auto& item : bagContents) {
      if (item == aThing) {
        bagCount++;
      }
    }
    return bagCount;
  }

  bool empty() const {
    return bagContents.empty();
  }

private:
  List<Thing> bagContents;
};
