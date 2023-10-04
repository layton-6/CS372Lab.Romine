// Helpful video of understanding the algorithm to delete the node https://www.youtube.com/watch?v=zUt2KB2hTQg&ab_channel=SimpleSnippets


template<typename V>
class Tree {
private:
   struct Node {
      Node(V v, shared_ptr<Node> l, shared_ptr<Node> r):
               value(v), left(l), right(r) {}
      V value;
      shared_ptr<Node> left;
      shared_ptr<Node> right;
   };
   shared_ptr<Node> root;

public:
   Tree() : root(nullptr) {}
   Tree(Tree const &lft, V value, Tree const &rgt) :
           root(make_shared<Node>(value, lft.root, rgt.root)) {}

   bool isEmpty() const { return !root; }
   V getRootValue() const { return root->value; }
   Tree getLeft() const { return Tree(root->left); }
   Tree getRight() const { return Tree(root->right); }

   bool member(V x) const {
      if (isEmpty()) {
         return false;
      } else if (x == getRootValue()) {
         return true;
      } else if (x < getRootValue()) {
         return getLeft().member(x);
      } else {
         return getRight().member(x);
      }
   }

   bool isLeaf() const {
      return !isEmpty() && !root->left && !root->right;
   }

   bool deleteNode(V x) {
      return deleteNode(root, x);
   }

private:
   bool deleteNode(shared_ptr<Node>& currentNode, V x) {
      if (!currentNode) {
         return false; // When the value can't be found in the tree
      }

      if (x < currentNode->value) {
         return deleteNode(currentNode->left, x);
      } else if (x > currentNode->value) {
         return deleteNode(currentNode->right, x);
      } else {
          // Node with the value to delete
         if (currentNode->left && currentNode->right) {
            // When there is a case with two children, replace with the minimum value in the right subtree
            currentNode->value = findMinValue(currentNode->right);
            return deleteNode(currentNode->right, currentNode->value);
         } else {
            // Returns true for cases with one child or no child
            currentNode = (currentNode->left) ? currentNode->left : currentNode->right;
            return true;
         }
      }
   }

   V findMinValue(shared_ptr<Node>& node) {
      while (node->left) {
         node = node->left;
      }
      return node->value;
   }
};
