// Write a function to find the diameter of binary tree.
// Diameter of a binary tree is the number of nodes on the longest path between two leaf nodes in the tree.
// Example : Tree considered here is :
//        1
//       / \
//     2   3
//    / \  / \
//   4   5 6  7
// Diameter of the tree is 4.

// Approach 1 : Recursive Approach (DFS)
// The diameter of a tree T is the largest of the following quantities:
// 1. The diameter of T’s left subtree
// 2. The diameter of T’s right subtree
// 3. The longest path between leaves that goes through the root of T (this can be computed from the heights of the subtrees of T)
// The time complexity for this approach is O(n^2) because for each node, we are calculating the height of the left and right subtree. Diameter function calls height() for every node, so O(N) × O(N) = O(N²).
// The space complexity for this approach is O(n) because of the recursive stack space.

// int diameterOfTree(Node* root) {
//     if (root == NULL) {
//         return 0;
//     }
//
//     int leftHeight = heightOfTree(root->left);
//     int rightHeight = heightOfTree(root->right);
//     int opt3 = leftHeight + rightHeight + 1;
//
//     int leftDiameter = diameterOfTree(root->left);
//     int opt1 = leftDiameter;
//     int rightDiameter = diameterOfTree(root->right);
//     int opt2 = rightDiameter;
//
//     return max(opt1, max(opt2, opt3));
// }

// Approach 2 : Optimized Approach (DFS)
// 1. Use a helper function that returns both height and diameter.
// 2. At each node:
//    Compute left and right subtree heights.
//    Compute left and right subtree diameters.
//    The diameter at that node is left height + right height.
// 3. Return both the height and maximum diameter.

// Step by Step Execution :
// 1. Starting from Node 4 and 5
//    height(4) = 1, diameter(4) = 0
//    height(5) = 1, diameter(5) = 0

// Node 2 Calculation
//    height(2) = max(1,1) + 1 = 2
//    diameter(2) = max(1+1, 0, 0) = 2


// 2. Similarly for Node 6 and 7
//    height(6) = 1, diameter(6) = 0
//    height(7) = 1, diameter(7) = 0

// Node 3 Calculation
//    height(3) = max(1,1) + 1 = 2
//    diameter(3) = max(1+1, 0, 0) = 2


// 3. Finally for Root Node 1
//    height(1) = max(2,2) + 1 = 3
//    diameter(1) = max(2+2, 2, 2) = 4
// ✅ Final Answer: Diameter = 4

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

pair<int, int> diameterOfTree(Node* root) {
    if (root == NULL) {
        return {0, 0};
    }

    pair<int, int> leftPair = diameterOfTree(root->left);
    pair<int, int> rightPair = diameterOfTree(root->right);

    int opt1 = leftPair.second;
    int opt2 = rightPair.second;
    int opt3 = leftPair.first + rightPair.first + 1;  // If we are considering node as a part of diameter then +1 and if we are considering edge as a part of diameter then no need to add +1

    int height = max(leftPair.first, rightPair.first) + 1;
    int diameter = max(opt1, max(opt2, opt3));

    return {height, diameter};
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
    pair<int, int> result = diameterOfTree(root);
    cout << "Diameter of the Tree (Optimized): " << result.second << endl;
    return 0;
}
