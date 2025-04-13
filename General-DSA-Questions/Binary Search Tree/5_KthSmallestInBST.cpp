// Write a function to find the kth smallest element in a Binary Search Tree (BST).

// Approach:
// 1. Perform an inorder traversal of the BST.
// 2. Maintain a count of visited nodes.
// 3. When the count reaches k, return the current node.
// 4. Time Complexity: O(N), where N is the number of nodes in the BST.
// 5. Space Complexity: O(H), where H is the height of the BST.

// To find the kth largest element, perform a reverse inorder traversal or (n - k + 1)th smallest element.

// Referal Link : https://takeuforward.org/data-structure/kth-largest-smallest-element-in-binary-search-tree/

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

// Function to find the kth smallest element in a BST
void inorder(Node* root, int k, int& counter, int& result) {
    // Base case: If the root is NULL or the count is greater than k, return
    if (root == NULL || counter > k) {
        return;
    }

    // Traverse the left subtree.
    inorder(root->left, k, counter, result);

    // Increment the count
    counter++;

    // If the count is equal to k, store the result
    if (counter == k) {
        result = root->data;
        return;
    }

    // Traverse the right subtree
    inorder(root->right, k, counter, result);
}

int kthSmallestElement(Node* root, int k) {
    int counter = 0;
    // Initialize the result to -1 and return -1 if the root is NULL
    int result = -1;

    inorder(root, k, counter, result);

    return result;
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(50);
  root->left = new Node(30);
  root->right = new Node(70);
  root->left->left = new Node(20);
  root->left->left->left = new Node(10);
  root->left->right = new Node(40);
  root->right->right = new Node(80);
  return root;
}

int main() {
    Node* root = createSampleBST();
    int k = 3;

    cout << "The kth smallest element in the BST is: " << kthSmallestElement(root, k) << endl;

    return 0;
}
// Tree Structure:
//         50
//        /  \
//       30   70
//      /  \    \
//     20  40   80
//    /
//   10
// The 3rd smallest element in the BST is 30.
