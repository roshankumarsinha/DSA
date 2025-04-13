// Find InOrder Predecessor and Successor in a BST
// Given a Binary Search Tree and a key, find the Inorder Predecessor and Successor of the key. In BST, the Inorder Predecessor of a node is the maximum value in the left subtree of the node, and the Inorder Successor is the minimum value in the right subtree of the node.

// Approach 1: (Store Inorder in an Array)
// 1. Perform an inorder traversal of the BST and store the elements in an array.
// 2. Find the index of the key in the array.
// 3. The Inorder Predecessor will be the element at index - 1, and the Inorder Successor will be the element at index + 1.
// 4. Time Complexity: O(N), where N is the number of nodes in the BST.
// 5. Space Complexity: O(N) for the array.

// Approach 2: (Iterative Approach)
// 1. Initialize the Inorder Predecessor and Successor as NULL.
// 2. If the key is found in the BST, the Inorder Predecessor will be the maximum value in the left subtree of the key, and the Inorder Successor will be the minimum value in the right subtree of the key.
// 3. If the key is not found, keep track of the last node visited while searching for the key.
// 4. The Inorder Predecessor will be the last node visited before the key, and the Inorder Successor will be the first node visited after the key.
// 5. Time Complexity: O(H), where H is the height of the BST.
// 6. Space Complexity: O(1).

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

// Function to find the Inorder Predecessor and Successor in a BST using Iterative Approach
void findPredecessorAndSuccessor(Node* root, Node* &predecessor, Node* &successor, int key) {
    while (root != NULL) {
        if (root->data < key) {
            predecessor = root;  // Store possible predecessor
            root = root->right;
        } else if (root->data > key) {
            successor = root;  // Store possible successor
            root = root->left;
        } else {  // If the key is found
            // Find Predecessor
            if (root->left) {
                predecessor = root->left;
                while (predecessor->right) predecessor = predecessor->right;  // Move to the rightmost node in the left subtree
            }
            // Find Successor
            if (root->right) {
                successor = root->right;
                while (successor->left) successor = successor->left;  // Move to the leftmost node in the right subtree
            }
            return;
        }
    }
}

// Function to create a sample BST
Node* createSampleTree() {
  Node* root = new Node(20);
  root->left = new Node(8);
  root->right = new Node(22);
  root->left->left = new Node(4);
  root->left->right = new Node(12);
  root->left->right->left = new Node(10);
  root->left->right->right = new Node(14);
  return root;
}

int main() {
    Node* root = createSampleTree();
    Node* predecessor = NULL;
    Node* successor = NULL;
    int key = 10;

    findPredecessorAndSuccessor(root, predecessor, successor, key);

    if (predecessor) {
        cout << "Inorder Predecessor of " << key << " is: " << predecessor->data << endl;
    } else {
        cout << "Inorder Predecessor of " << key << " is: NULL" << endl;
    }

    if (successor) {
        cout << "Inorder Successor of " << key << " is: " << successor->data << endl;
    } else {
        cout << "Inorder Successor of " << key << " is: NULL" << endl;
    }

    return 0;
}

// Tree Structure:
//         20
//        /  \
//       8   22
//      / \
//     4  12
//        / \
//       10 14
// Key: 10
// The Inorder Predecessor of 10 is 8.
// The Inorder Successor of 10 is 12.
