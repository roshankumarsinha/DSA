// Write a function to perform boundary traversal of a binary tree.
// Boundary traversal of a binary tree consists of three parts:
// 1. Left Boundary (excluding leaf nodes)
// 2. Leaf Nodes (from left to right)
// 3. Right Boundary (excluding leaf nodes, printed in reverse)
// Example:
// Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6
//       / \
//      7   8
// Boundary Traversal : 1 2 4 5 7 8 6 3

// Approach: Recursive Approach
// 1. We will create three functions to print the left boundary, leaf nodes, and right boundary.
// 2. We will start with the root node and print the root node.
// 3. We will call the function to print the left boundary.
//    3.1. We will print the left boundary of the left subtree by traversing the left child of the root node.
// 4. We will call the function to print the leaf nodes.
//    4.1. We will print the leaf nodes by traversing the left and right children of the root node.
// 5. We will call the function to print the right boundary.
//    5.1. We will print the right boundary of the right subtree by traversing the right child of the root node.
// 6. The time complexity for this approach is O(n) where n is the number of nodes in the tree.
// 7. The space complexity for this approach is O(n) because of the recursive stack space.

#include <iostream>
#include <vector>
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

// Function to print the left boundary of the tree
void printLeftBoundary(Node* root, vector<int>& result) {
  // Base Case
  if (root == NULL) {
    return;
  }
  if (root->left == NULL && root->right == NULL) {  // If it is a leaf node, return
    return;
  }

  result.push_back(root->data);  // Print the node
  if (root->left) {
    printLeftBoundary(root->left, result);  // Recursively print the left boundary of the left subtree
  } else {
    printLeftBoundary(root->right, result);  // If left child is NULL, print the left boundary of the right subtree
  }
}

// Function to print the leaf nodes of the tree. This is InOrder Traversal
void printLeafNodes(Node* root, vector<int>& result) {
  // Base Case
  if (root == NULL) {
    return;
  }

  printLeafNodes(root->left, result);  // Recursively print the leaf nodes of the left subtree
  if (root->left == NULL && root->right == NULL) {  // If it is a leaf node, print the node
    result.push_back(root->data);
  }
  printLeafNodes(root->right, result);  // Recursively print the leaf nodes of the right subtree
}

// Function to print the right boundary of the tree
void printRightBoundary(Node* root, vector<int>& result) {
  // Base Case
  if (root == NULL) {
    return;
  }
  if (root->left == NULL && root->right == NULL) {  // If it is a leaf node, return
    return;
  }

  if (root->right) {
    printRightBoundary(root->right, result);  // Recursively print the right boundary of the right subtree
  } else {
    printRightBoundary(root->left, result);  // If right child is NULL, print the right boundary of the left subtree
  }
  result.push_back(root->data);  // Print the node in reverse order. Note: We have added this line in end compare to printLeftBoundary()
}

// Function to perform boundary traversal of a binary tree
vector<int> boundaryTraversal(Node* root) {
  vector<int> result;  // Vector to store the nodes of the tree
  if (root == NULL) {
    return result;
  }

  result.push_back(root->data);  // Print the root node
  printLeftBoundary(root->left, result);  // Print the left boundary of the tree
  printLeafNodes(root, result);  // Print the leaf nodes of the tree
  printRightBoundary(root->right, result);  // Print the right boundary of the tree

  return result;
}

// Function to create a sample tree
Node* createSampleTree() {
  Node* root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  root->right->right = new Node(6);
  root->left->right->left = new Node(7);
  root->left->right->right = new Node(8);
  return root;
}

int main() {
  Node* root = createSampleTree();
  vector<int> result = boundaryTraversal(root);
  cout << "Boundary Traversal (Recursive): ";
  for (int val : result) {
    cout << val << " ";
  }
  cout << endl;
  return 0;
}