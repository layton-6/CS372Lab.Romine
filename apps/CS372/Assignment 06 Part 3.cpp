// William Romine
// 00103649
// Dr. Lewis CS372

// GeeksforGeeks has been really helpful for these Binary Searches: https://www.geeksforgeeks.org/randomized-binary-search-algorithm/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

struct Struct_VectorTree {
    size_t type_size;
    std::vector<int> arr;
    TreeNode* tree;
};

bool createStructure(Struct_VectorTree* &structure, size_t numItems) {
    if (numItems == 0) {
        return false;
    }

    structure = new Struct_VectorTree;
    structure->type_size = numItems;

    for (size_t i = 0; i < numItems; ++i) {
        structure->arr.push_back(rand() % 100);
    }

    std::sort(structure->arr.begin(), structure->arr.end());

    structure->tree = nullptr;

    // Binary Search Tree
    for (int item : structure->arr) {
        TreeNode* newNode = new TreeNode(item);
        if (structure->tree == nullptr) {
            structure->tree = newNode;
        } else {
            TreeNode* current = structure->tree;
            while (true) {
                if (item < current->data) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    return true;
}

bool binarySearchVector(const std::vector<int>& aSortedVector, int itemToBeFound) {
    int right = aSortedVector.size() - 1;
    int left = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (aSortedVector[mid] == itemToBeFound) {
            return true;
        }

        if (aSortedVector[mid] < itemToBeFound) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

bool binarySearchTree(TreeNode* root, int itemToBeFound) {
    TreeNode* current = root;
    while (current != nullptr) {
        if (itemToBeFound == current->data) {
            return true;
        } else if (itemToBeFound < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<size_t> sizes = {1000, 2500, 5000, 10000, 50000};

    for (size_t numItems : sizes) {
        Struct_VectorTree* myStruct = nullptr;
        if (createStructure(myStruct, numItems)) {
            std::cout << "Structure created with " << myStruct->type_size << " items." << std::endl;

            std::vector<int> randomNumbersToSearch;
            for (int i = 0; i < 100; ++i) {
                randomNumbersToSearch.push_back(rand() % 100);
            }

            auto start = std::chrono::high_resolution_clock::now();
            for (int item : randomNumbersToSearch) {
                bool found = binarySearchVector(myStruct->arr, item);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Binary Search Time (Vector) for " << numItems << " items: " << duration.count() << " microseconds" << std::endl;

            start = std::chrono::high_resolution_clock::now();
            for (int item : randomNumbersToSearch) {
                bool found = binarySearchTree(myStruct->tree, item);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Binary Search Time (Tree) for " << numItems << " items: " << duration.count() << " microseconds" << std::endl;

            delete myStruct;
        } else {
            std::cout << "Invalid number of items. Structure not created." << std::endl;
        }
    }

    return 0;
}

