// William Romine
// 00103649
// Dr. Lewis CS372

#include "vector.h"
#include <iostream>

class ReceiptBag {
private:
    std::vector<int> items;
    std::vector<int> receipts;
    int currentReceipt = 1;

public:
    int insert(int item) {
        items.push_back(item);
        receipts.push_back(currentReceipt);
        return currentReceipt++;
    }

    int remove(int receipt) {
        for (size_t i = 0; i < receipts.size(); ++i) {
            if (receipts[i] == receipt) {
                int removedItem = items[i];
                items.erase(items.begin() + i);
                receipts.erase(receipts.begin() + i);
                return removedItem;
            }
        }
        return -1;
    }
};

int main() {
    ReceiptBag bag;

    int receipt1 = bag.insert(10);
    int receipt2 = bag.insert(20);
    int receipt3 = bag.insert(30);

    std::cout << "Items in the bag: " << std::endl;
    std::cout << bag.remove(receipt1) << std::endl;
    std::cout << bag.remove(receipt2) << std::endl;
    std::cout << bag.remove(receipt3) << std::endl;

    return 0;
}
