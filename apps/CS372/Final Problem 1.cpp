// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include <memory>

template<typename V>
class Tree {
public:
    struct Node {
        Node(V v, std::shared_ptr<Node> lft = nullptr, std::shared_ptr<Node> rgt = nullptr) :
            value(v), left(lft), right(rgt) {}

        V value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    std::shared_ptr<Node> root;

public:
    Tree() : root(nullptr) {}
    Tree(const Tree &lft, V value, const Tree &rgt) :
        root(std::make_shared<Node>(value, lft.root, rgt.root)) {}

    bool deleteNode(V x) {
        return deleteNode(root, x);
    }

    std::shared_ptr<Node> getRoot() const {
        return root;
    }
};

// Function to count the number of nodes in the tree
template<typename V>
int countNodes(const std::shared_ptr<typename Tree<V>::Node>& root) {
    if (!root) {
        return 0;
    }
    return 1 + countNodes<V>(root->left) + countNodes<V>(root->right);
}

// Function to count the number of internal (non-leaf) nodes in the tree
template<typename V>
int countInternalNodes(const std::shared_ptr<typename Tree<V>::Node>& root) {
    if (!root || (!root->left && !root->right)) {
        return 0;
    }
    return 1 + countInternalNodes<V>(root->left) + countInternalNodes<V>(root->right);
}

// Function to compute the external path length of the tree
template<typename V>
void computeExternalPathLength(const std::shared_ptr<typename Tree<V>::Node>& root, int& summation) {
    if (!root) {
        return;
    }
    summation += 1;
    computeExternalPathLength<V>(root->left, summation);
    computeExternalPathLength<V>(root->right, summation);
}

int main() {
    // For Example
    std::shared_ptr<Tree<int>::Node> root = std::make_shared<Tree<int>::Node>(1);
    root->left = std::make_shared<Tree<int>::Node>(2);
    root->right = std::make_shared<Tree<int>::Node>(3);

    // Use the functions outside the class function
    int nodeCount = countNodes<int>(root);
    std::cout << "Number of nodes: " << nodeCount << std::endl;

    int internalNodeCount = countInternalNodes<int>(root);
    std::cout << "Number of internal nodes: " << internalNodeCount << std::endl;

    int externalPathLength = 0;
    computeExternalPathLength<int>(root, externalPathLength);
    std::cout << "External path length: " << externalPathLength << std::endl;

    return 0;
}
