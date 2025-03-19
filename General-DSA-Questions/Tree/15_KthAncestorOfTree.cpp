// Write a function to find the kth ancestor of a node in a binary tree.
// The Kth ancestor of a node in a binary tree is the Kth parent when moving upwards from the given node.

// Example:
// Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6
// Find 2nd ancestor of Node 4
//  1.  1st Ancestor of 4 → 2
//  2.  2nd Ancestor of 4 → 1 ✅

// Approach 1:
// 1. One easy approach is to store the ancestors of each node in an array.
// 2. Traverse the tree and store the ancestors of each node in an array.
// 3. Find the Kth ancestor of the given node using the array.
// 4. The time complexity for this approach is O(n) where n is the number of nodes in the tree.
// 5. The space complexity for this approach is O(n) where n is the number of nodes in the tree.

// Approach 2:
// 1. Base Case:
//    a.  If root == NULL, return NULL (no ancestor found).
//    b.  If root->data == node, return root (we found the target node).

// 2. Recursive Calls:
//    a.  Recur on the left subtree (solve(root->left, k, node))
//    b.  Recur on the right subtree (solve(root->right, k, node))

// 3. Backtracking to Find Ancestor: (While going back to the parent node)
//    a.  If the node is found in the left subtree, backtrack and decrement k.
//    b.  If k == 0, the current node is the Kth ancestor, so we store the answer and prevent further decrements by setting k = INT_MAX.
//    c.  Return the valid ancestor from the left or right subtree.

// 4. Final Check in kthAncestor Function:
//    a.  If ans == NULL (target node not found) or ans->data == node (we never reached Kth ancestor), return -1.
//    b.  Otherwise, return ans->data.

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

// Function to find the Kth ancestor of a node in a binary tree
Node* solve(Node* root, int node, int &k) {  // Here, node represents the node whose Kth ancestor is to be found and k represents the value of K
    // Base Case
    if (root == NULL) {
        return NULL;
    }

    // We found the given node so pass the value to the parent node
    if (root->data == node) {
        return root;
    }

    // Recursively find the Kth ancestor in the left subtree
    Node* leftAns = solve(root->left, node, k);
    // Recursively find the Kth ancestor in the right subtree
    Node* rightAns = solve(root->right, node, k);

    // If we found the node in the left subtree
    if (leftAns != NULL && rightAns == NULL) {  // If left subtree has node and right subtree does not have node
        k--;  // Decrement the value of K, as we are moving upwards
        if (k == 0) {  // If K becomes 0, then we have found the Kth ancestor
            k = INT_MAX;  // Reset the value of K, we are storing max value of int because we want to lock this root node as this node will be the answer. So if we add int max then it's not possible to make k = 0 again.
            return root;  // Return the root node
        }
        else {
            return leftAns;  // Return the left ancestor
        }
    }

    // If we found the node in the right subtree
    if (rightAns != NULL && leftAns == NULL) {  // If right subtree has node and left subtree does not have node
        k--;  // Decrement the value of K, as we are moving upwards
        if (k == 0) {  // If K becomes 0, then we have found the Kth ancestor
            k = INT_MAX;  // Reset the value of K, we are storing max value of int because we want to lock this root node as this node will be the answer. So if we add int max then it's not possible to make k = 0 again.
            return root;  // Return the root node
        }
        else {
            return rightAns;  // Return the right ancestor
        }
    }

    return NULL;  // If the node is not found in the subtree, return NULL
}

int kthAncestor(Node* root, int node, int k) {
    Node* ans = solve(root, node, k);  // Call the solve function to find the Kth ancestor of the given node
    if (ans == NULL || ans->data == node) {  // If the node is not found or the node is the root node, because the value of k must be greater than 0. so, if we have root node as the answer then we will return -1 because for root node we don't have any ancestor.
        return -1;  // Return -1 if the node is not found or the node is the root node
    }
    else {
        return ans->data;  // Return the data of the Kth ancestor
    }
}

// Function to create a sample tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    return root;
}

int main() {
    Node* root = createSampleTree();
    int node = 4;
    int k = 2;
    cout << "The " << k << "nd ancestor of Node " << node << " is: " << kthAncestor(root, node, k) << endl;
    return 0;
}
