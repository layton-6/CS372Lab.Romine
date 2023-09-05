// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include "bag.h"

int main() {

    int receipt1 = bag.insert(10);
    int receipt2 = bag.insert(20);
    int receipt3 = bag.insert(30);

    std::cout << "Items in the bag: " << std::endl;
    std::cout << bag.remove(receipt1) << std::endl;
    std::cout << bag.remove(receipt2) << std::endl;
    std::cout << bag.remove(receipt3) << std::endl;

    return 0;
}
