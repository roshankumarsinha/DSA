// Write a function to check if a binary tree is a max-heap or not.

// To determine whether a given binary tree satisfies the properties of a Max-Heap, you need to check two conditions:
// 1. Complete Binary Tree (CBT)
//    a.  All levels are fully filled except possibly the last, which must be filled from left to right.
// 2. Heap Order Property
//    a.  Every node’s value must be greater than or equal to its children's values.

// Approach:
// 1. Perform a level-order traversal of the binary tree to check if it is a complete binary tree.
// 2. During the traversal, check if each node satisfies the heap order property.
// 3. If both conditions are satisfied, the binary tree is a max-heap.
// 4. Time Complexity: O(N) for checking both conditions.
// 5. Space Complexity: O(N) for storing the level-order traversal.

#include <iostream>
#include <queue>
using namespace std;

// Definition of a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to check if a binary tree is a complete binary tree
bool isCompleteBinaryTree(Node* root) {
    // A null tree is considered as heap
    if (root == nullptr)
        return true;

    queue<Node*> q;
    q.push(root);

    // Flag to indicate if a null child has been seen, which means we have reached the last level
    // Once we see a node missing a child,
      // ➡️ no more child nodes should exist after that in the level-order sequence.
    bool nullChildSeen = false;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Left child check
        if (current->left) {
            // If we have seen a null child before and the current node's left child is not null,
            // or if the current node's data is less than its left child's data, return false
            if (nullChildSeen || current->data < current->left->data)
                return false;
            q.push(current->left);
        } else {  // If the left child is null, we have seen a null child
            nullChildSeen = true;
        }

        // Right child check
        if (current->right) {
            // If we have seen a null child before and the current node's right child is not null,
            // or if the current node's data is less than its right child's data, return false
            if (nullChildSeen || current->data < current->right->data)
                return false;
            q.push(current->right);
        } else {  // If the right child is null, we have seen a null child
            nullChildSeen = true;
        }
    }

    return true;
}

int main() {
  Node* root = new Node(10);
  root->left = new Node(9);
  root->right = new Node(8);
  root->left->left = new Node(7);
  // root->right->left = new Node(6);  // Uncomment this line to make Binary Tree not a max-heap

  if (isCompleteBinaryTree(root)) {
      cout << "The binary tree is a max-heap." << endl;
  } else {
      cout << "The binary tree is not a max-heap." << endl;
  }
}