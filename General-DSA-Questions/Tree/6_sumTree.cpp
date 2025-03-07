// Write a function to check if a binary tree is a sum tree or not.
// A Sum Tree is a binary tree where the value of each non-leaf node is equal to the sum of the values of its left and right subtrees.
// Example : Tree considered here is :
//        26
//       /  \
//     10    3
//    /  \     \
//   4    6     3
// 10 = 4 + 6
// 3 = 0 + 3 (Leaf nodes count as 0)
// 26 = 10 + 3 + 4 + 6 + 3
// ✅ Output: Yes, it is a Sum Tree.

// Approach : Recursive Approach
// 1. Create a pair where first element is a boolean to check if the tree is a sum tree and the second element is the sum of the tree.
// 2. If the root is NULL, return {true, 0}.
// 3. If the root is a leaf node, return {true, root->data}.
// 4. Recursively check if the left subtree is a sum tree.
// 5. Recursively check if the right subtree is a sum tree.
// 6. If both the left and right subtrees are sum trees and the sum of the left subtree is equal to the sum of the right subtree, return {true, 2 * root->data}. 2 * root->data = root->data + left subtree sum + right subtree sum.
// 7. If any of the conditions are not satisfied, return {false, 0}.
// 8. The time complexity for this approach is O(n) because we are traversing each node only once.
// 9. The space complexity for this approach is O(n) because of the recursive stack space.

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// Function to check if a binary tree is a sum tree or not
pair<int, bool> checkSumTree(Node* root) {
  if (root == NULL) {   // Empty tree is a Sum Tree
    return {0, true};
  }

  if (root->left == NULL && root->right == NULL) {   // Leaf node
    return {root->data, true};    // Sum of leaf node is the value of the node
  }

  pair<int, bool> left = checkSumTree(root->left);  // Recursively check if the left subtree is a sum tree
  pair<int, bool> right = checkSumTree(root->right);  // Recursively check if the right subtree is a sum tree

  bool isSumTree = left.second && right.second && (root->data == left.first + right.first);  // If both the left and right subtrees are sum trees and the sum of the left subtree is equal to the sum of the right subtree

  return {root->data + left.first + right.first, isSumTree};  // 2 * root->data = root->data + left subtree sum + right subtree sum

}

// Function to create a sample tree
Node* createSumTree() {
  Node* root = new Node(26);
  root->left = new Node(10);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(6);
  root->right->right = new Node(3);
  return root;
}

int main() {
  Node* root = createSumTree();
  pair<int, bool> result = checkSumTree(root);
  if (result.second) {
    cout << "Yes, it is a Sum Tree." << endl;
  } else {
    cout << "No, it is not a Sum Tree." << endl;
  }
  return 0;
}