// Write a function to validate a Binary Search Tree (BST).

// Approach 1: Inorder Traversal (Inorder Traversal of valid BST is always sorted)
// 1. Perform an inorder traversal of the BST.
// 2. Store the elements in an array.
// 3. Check if the array is sorted.
// 4. If the array is sorted, return true; otherwise, return false.
// 5. Time Complexity: O(N), where N is the number of nodes in the BST.
// 6. Space Complexity: O(N) for the array.

// Approach 2: Recursive Approach
// 1. For each node, check if the node's value is within the valid range.
// 2. For the left child, the value should be less than the current node's value and greater than the minimum value.
// 3. For the right child, the value should be greater than the current node's value and less than the maximum value.
// 4. Recursively check the left and right subtrees.
// 5. Time Complexity: O(N), where N is the number of nodes in the BST.
// 6. Space Complexity: O(H), where H is the height of the BST.

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

// Function to validate a BST using Recursive Approach
bool isValidBST(Node* root, long long int minVal, long long int maxVal) {
    // Base case: If the root is NULL, return true
    if (root == NULL) {
        return true;
    }

    // Check if the current node's value is within the valid range
    if (root->data >= minVal && root->data <= maxVal) {
        // Recursively check the left and right subtrees
        // For the left child, minimum value remains the same, and the maximum value becomes the current node's value
        // For the right child, maximum value remains the same, and the minimum value becomes the current node's value
        return isValidBST(root->left, minVal, root->data) && isValidBST(root->right, root->data, maxVal);
    } else {
        return false;
    }
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(5);
  root->left = new Node(3);
  root->right = new Node(7);
  root->left->left = new Node(2);
  root->left->right = new Node(4);
  root->right->left = new Node(6);
  root->right->right = new Node(8);
  return root;
}

int main() {
    Node* root = createSampleBST();

    // Validate the BST
    if (isValidBST(root, LLONG_MIN, LLONG_MAX)) {   // LLONG_MIN and LLONG_MAX are the minimum and maximum values of long long int
        cout << "The given tree is a valid BST." << endl;
    } else {
        cout << "The given tree is not a valid BST." << endl;
    }

    return 0;
}

// Example :
// Tree Created is :
//         5
//        / \
//       3   7
//      / \ / \
//     2  4 6  8