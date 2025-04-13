// Write a function to find the lowest common ancestor in a binary search tree.
// LCA is the lowest node in the tree that has both p and q as descendants (where we allow a node to be a descendant of itself).

// Approach 1: Recursive
// 1. Start traversing the tree from the root node.
// 2. If both p and q are in the right subtree, then continue the search with the right subtree starting step 1.
// 3. If both p and q are in the left subtree, then continue the search with the left subtree starting step 1.
// 4. If both the above cases are false, this means we have found the node which is common to node p's and q's subtrees. and hence we return this common node as the LCA.


// If both nodes lie in the left subtree, the LCA must be in the left subtree.
// If both nodes lie in the right subtree, the LCA must be in the right subtree.
// If one node is on the left and the other is on the right (or one of them is the current node itself), then the current node is the LCA.

// Time complexity: O(N) where N is the number of nodes in the BST.
// Space complexity: O(H) where H is the height of the BST.

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to find the LCA of two nodes in a BST using recursion
Node* LCAinBST(Node* root, Node* p, Node* q) {
    // If the root is NULL, return NULL
    if (root == NULL) return NULL;

    // If both nodes are smaller than the root, then the LCA lies in the left subtree
    if (root->data > p->data && root->data > q->data) {
        return LCAinBST(root->left, p, q);
    }

    // If both nodes are greater than the root, then the LCA lies in the right subtree
    if (root->data < p->data && root->data < q->data) {
        return LCAinBST(root->right, p, q);
    }

    // If one node is on the left and the other is on the right (or one of them is the current node itself), then the current node is the LCA
    return root;
}

// We can solve it using iterative approach also. Space complexity will be O(1) in that case.
// Iterative approach to find the LCA of two nodes in a BST
// Node* LCAinBST(Node* root, Node* p, Node* q) {
//     while (root != NULL) {
//         if (root->data > p->data && root->data > q->data)
//             root = root->left;   // Move to the left subtree
//         else if (root->data < p->data && root->data < q->data)
//             root = root->right;  // Move to the right subtree
//         else
//             return root;     // If one node is on the left and the other is on the right (or one of them is the current node itself), then the current node is the LCA
//     }
//     return NULL;     // If the root is NULL, return NULL
// }

// Function to create a sample BST
Node* createSampleTree() {
  Node* root = new Node(6);
  root->left = new Node(2);
  root->right = new Node(8);
  root->left->left = new Node(0);
  root->left->right = new Node(4);
  root->left->right->left = new Node(3);
  root->left->right->right = new Node(5);
  root->right->left = new Node(7);
  root->right->right = new Node(9);
  return root;
}

int main() {
    Node* root = createSampleTree();
    Node* p = root->left->right;  // Node with value 4
    Node* q = root->left;        // Node with value 2
    Node* lca = LCAinBST(root, p, q);
    cout << "LCA of " << p->data << " and " << q->data << " is " << lca->data << endl;
    return 0;
}

// Tree Structure:
//         6
//       /   \
//      2     8
//     / \   / \
//    0   4 7   9
//       / \
//      3   5

// LCA of 4 and 2 is 2
