// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

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

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int choice;
    do {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Create a Structure" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                size_t numItems;
                std::cout << "Enter the number of items: ";
                std::cin >> numItems;

                Struct_VectorTree* myStruct = nullptr;
                if (createStructure(myStruct, numItems)) {
                    std::cout << "Structure created with " << myStruct->type_size << " items." << std::endl;

                    std::cout << "Sorted Array: ";
                    for (int item : myStruct->arr) {
                        std::cout << item << " ";
                    }
                    std::cout << std::endl;

                    // Free Up Memory
                    deleteTree(myStruct->tree);
                    delete myStruct;
                } else {
                    std::cout << "Invalid number of items. Structure not created." << std::endl;
                }

                break;
            }
            case 2:
                std::cout << "Exiting." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please choose again." << std::endl;
                break;
        }

    } while (choice != 2);

    return 0;
}

