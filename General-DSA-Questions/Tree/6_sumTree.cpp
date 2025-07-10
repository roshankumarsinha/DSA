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

// Better solution is :-
// Approach 2 : Optimized Approach (DFS) - Using Global Variable
// #include <iostream>

// using namespace std;

// // Definition for a binary tree node
// struct Node {
//     int data;
//     Node* left;
//     Node* right;

//     Node(int val) : data(val), left(nullptr), right(nullptr) {}
// };

// class Solution {
// public:
//     // Helper function that returns:
//     //   - sum of subtree rooted at current node, if subtree is a Sum Tree
//     //   - -1 if subtree is not a Sum Tree
//     int checkSumTree(Node* node) {
//         if (node == nullptr)
//             return 0;

//         // Leaf node
//         if (node->left == nullptr && node->right == nullptr)
//             return node->data;

//         // Recursively get sums of left subtrees
//         int leftSum = checkSumTree(node->left);

//         If left subtree is invalid, propagate failure
//         if (leftSum == -1)
//             return -1;

//         Recursively get sums of right subtrees
//         int rightSum = checkSumTree(node->right);

//         If right subtree is invalid, propagate failure
//         if (rightSum == -1)
//             return -1;   // Propagate failure -1 up the call stack

//         // Check the Sum Tree condition
//         if (node->data != leftSum + rightSum)
//             return -1;

//         // Return total sum including this node
//         return node->data + leftSum + rightSum;
//     }

//     bool isSumTree(Node* root) {
//         return checkSumTree(root) != -1;
//     }
// };

// int main() {
//     /*
//         Example Tree:
//                 26
//                /  \
//              10    3
//             / \     \
//            4   6     3

//         This is a Sum Tree because:
//         - 10 = 4 + 6
//         - 3 = 0 + 3
//         - 26 = 10 + 3 + (10's children) + (3's children)
//                = 10 + 3 + 4 + 6 + 3
//                = 26 (including children sums twice)
        
//         BUT actually in standard Sum Tree definitions, the sum of subtree is total sum of *all nodes below*.
//         So to match the simpler convention, we can define:
//         - Node's data = sum of *immediate* left and right subtree data.
//         So in this convention:
//         - For node 26:
//             leftSum = 10
//             rightSum = 3
//             10 + 3 = 13 != 26, so it's not a Sum Tree.
        
//         **Alternate simpler convention:**
//         Node value = sum of left subtree total sum + right subtree total sum.
//         So, in that convention, to avoid confusion, here's a clearer code:
        
//         A simpler, commonly used Sum Tree definition is:
//         - For non-leaf node:
//             node.data = sum of values of all nodes in left + right subtree.
        
//         So, we modify helper to return total sum as:
//         totalSum = node.data * 2
//         for non-leaf node.
        
//         **We will use this simpler definition below.**
//     */

//     // Build the example tree matching that definition:
//     Node* root = new Node(26);
//     root->left = new Node(10);
//     root->right = new Node(3);
//     root->left->left = new Node(4);
//     root->left->right = new Node(6);
//     root->right->right = new Node(3);

//     Solution sol;
//     bool isSum = sol.isSumTree(root);

//     if (isSum)
//         cout << "The binary tree is a Sum Tree." << endl;
//     else
//         cout << "The binary tree is NOT a Sum Tree." << endl;

//     // Clean up memory
//     delete root->left->left;
//     delete root->left->right;
//     delete root->left;
//     delete root->right->right;
//     delete root->right;
//     delete root;

//     return 0;
// }
