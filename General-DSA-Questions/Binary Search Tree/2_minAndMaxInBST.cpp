// Write a function to find the minimum and maximum value in a Binary Search Tree (BST).

// Approach:
// 1. The minimum value in a BST is the leftmost node in the tree.
// 2. The maximum value in a BST is the rightmost node in the tree.
// 3. To find the minimum value, keep moving to the left child until the left child is NULL.
// 4. To find the maximum value, keep moving to the right child until the right child is NULL.
// 5. Return the minimum and maximum values.
// 6. Time Complexity: O(H), where H is the height of the tree.
// 7. Space Complexity: O(1).

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

// Function to find the minimum value in a BST
int findMin(Node* root) {
    // Keep moving to the left child until the left child is NULL
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

// Function to find the maximum value in a BST
int findMax(Node* root) {
    // Keep moving to the right child until the right child is NULL
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(50);
  root->left = new Node(30);
  root->right = new Node(70);
  root->left->left = new Node(20);
  root->left->right = new Node(40);
  root->right->right = new Node(80);
  return root;
}

int main() {
    Node* root = createSampleBST();

    cout << "Minimum value in the BST: " << findMin(root) << endl;
    cout << "Maximum value in the BST: " << findMax(root) << endl;

    return 0;
}

// Tree Structure:
//         50
//        /  \
//       30   70
//      /  \    \
//     20  40   80

// Output:
// Minimum value in the BST: 20
// Maximum value in the BST: 80