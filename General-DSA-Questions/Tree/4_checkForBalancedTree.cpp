// Write a function to check if a binary tree is balanced or not.
// A Balanced Binary Tree is a tree in which the height difference between the left and right subtrees of any node is at most 1.

// Approach 1 : Recursive Approach
// 1. Compute the height of the left and right subtrees.
// 2. Check if the left subtree is balanced.
// 3. Check if the right subtree is balanced.
// 4. If the left and right subtrees are balanced, check if the height difference is at most 1. If |left height - right height| ≤ 1, return true.
// 5. If any of the subtrees is unbalanced, return false.
// 6. The time complexity for this approach is O(n^2) because for each node, we are calculating the height of the left and right subtree. IsBalanced function calls height() for every node, so O(N) × O(N) = O(N²).
// 7. The space complexity for this approach is O(n) because of the recursive stack space.

// bool isBalanced(Node* root) {
//     if (root == NULL) {
//         return true;
//     }
//
//     int leftHeight = heightOfTree(root->left);
//     int rightHeight = heightOfTree(root->right);
//
//     bool leftBalanced = isBalanced(root->left);
//     bool rightBalanced = isBalanced(root->right);
//     bool diff = abs(leftHeight - rightHeight) <= 1;
//
//     if (leftBalanced && rightBalanced && diff) {
//         return true;
//     }
//     return false;
// }

// Approach 2 : Optimized Approach
// 1. Use a helper function that returns both height and balance status.
// 2. At each node:
//    Compute left and right subtree heights.
//    Check if the left subtree is balanced.
//    Check if the right subtree is balanced.
//    The height at that node is max(left height, right height) + 1.
//    The balance status is true if both subtrees are balanced and the height difference is at most 1.
// 3. Return both the height and balance status.

// Step by Step Execution :

// 1. Starting from Leaf Nodes (4, 5, 6, 7)
//    height(4) = 1, isBalanced(4) = true
//    height(5) = 1, isBalanced(5) = true
//    height(6) = 1, isBalanced(6) = true
//    height(7) = 1, isBalanced(7) = true


// 2. For Node 2
//    leftHeight = 1 (Node 4), rightHeight = 1 (Node 5)
//    height(2) = max(1,1) + 1 = 2
//    isBalanced(2) = abs(1 - 1) ≤ 1 = true


// 3. For Node 3
//    leftHeight = 1 (Node 6), rightHeight = 1 (Node 7)
//    height(3) = max(1,1) + 1 = 2
//    isBalanced(3) = abs(1 - 1) ≤ 1 = true


// 4. For Root Node 1
//    leftHeight = 2 (Node 2), rightHeight = 2 (Node 3)
//    height(1) = max(2,2) + 1 = 3
//    isBalanced(1) = abs(2 - 2) ≤ 1 = true

// ✅ Final Answer: Tree is Balanced.

// The time complexity for this approach is O(n) because we are traversing each node only once.
// The space complexity for this approach is O(n) because of the recursive stack space.

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

pair<int, bool> isBalanced(Node* root) {
    if (root == NULL) {
        return {0, true};
    }

    pair<int, bool> left = isBalanced(root->left);
    pair<int, bool> right = isBalanced(root->right);
    
    bool leftBalanced = left.second;
    bool rightBalanced = right.second;
    bool diff = abs(left.first - right.first) <= 1;

    int height = max(left.first, right.first) + 1;
    bool isBalanced = leftBalanced && rightBalanced && diff;

    return {height, isBalanced};
}

Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    return root;
}

int main() {
    Node* root = createSampleTree();
    pair<int, bool> result = isBalanced(root);
    if (result.second) {
        cout << "Tree is Balanced." << endl;
    } else {
        cout << "Tree is not Balanced." << endl;
    }
    return 0;
}