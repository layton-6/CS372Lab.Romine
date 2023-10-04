#include <iostream>
#include <memory>

template <typename V>
struct TreeNode {
    V value;
    std::shared_ptr<TreeNode<V>> left;
    std::shared_ptr<TreeNode<V>> right;

    TreeNode(V val) : value(val), left(nullptr), right(nullptr) {}
};

template <typename V>
bool isLeaf(const std::shared_ptr<TreeNode<V>>& node) {
    return node && !node->left && !node->right;
}

template <typename V>
std::shared_ptr<TreeNode<V>> copyTreeWithoutLeavesHelper(const std::shared_ptr<TreeNode<V>>& originalNode) {
    if (!originalNode) {
        return nullptr;
    }

    if (isLeaf(originalNode)) {
        return nullptr;
    }

    // Copy the left and right subtrees
    std::shared_ptr<TreeNode<V>> newLeft = copyTreeWithoutLeavesHelper(originalNode->left);
    std::shared_ptr<TreeNode<V>> newRight = copyTreeWithoutLeavesHelper(originalNode->right);

    // Create a new node with the same value and the modified left and right subtrees
    return std::make_shared<TreeNode<V>>(originalNode->value, newLeft, newRight);
}

// Function to create a new tree without leaves
template <typename V>
std::shared_ptr<TreeNode<V>> copyTreeWithoutLeaves(const std::shared_ptr<TreeNode<V>>& originalRoot) {
    return copyTreeWithoutLeavesHelper(originalRoot);
}

int main() {
    // Create the original tree
    std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(1);
    root->left = std::make_shared<TreeNode<int>>(2);
    root->right = std::make_shared<TreeNode<int>>(3);
    root->left->left = std::make_shared<TreeNode<int>>(4);
    root->left->right = std::make_shared<TreeNode<int>>(5);
    root->right->left = std::make_shared<TreeNode<int>>(6);

    // Create a new tree without leaves
    std::shared_ptr<TreeNode<int>> newTree = copyTreeWithoutLeaves(root);

    return 0;
}
// This was a helpful article for me to understand the concept a little better https://www.geeksforgeeks.org/check-whether-binary-tree-full-binary-tree-not/
