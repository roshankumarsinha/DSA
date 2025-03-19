// Write a function to find the sum of the longest bloodline of a tree.
// The sum of the longest bloodline of a tree is the sum of the nodes on the longest path from the root node to the leaf node. If there are multiple paths with the same length, consider the path that has the maximum sum of nodes.

// Example:
// Tree considered here is :
//        1
//       / \
//      2   3
//     /     \
//    4       5
//   /         \
//  7           8

// Possible paths from the root to the leaf nodes are:
// 1 -> 2 -> 4 -> 7 (Sum = 14)  && 1 -> 3 -> 5 -> 8 (Sum = 17), so answer is 17.

// Approach:
// 1. Use DFS (Preorder Traversal) to traverse all root-to-leaf paths.
// 2. Track maxLength (maximum depth) and maxSum (sum at max depth).
// 3. Update maxSum whenever a longer path is found.

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

// Function to find the sum of the longest bloodline of a tree
void findLongestPathSum(Node* root, int depth, int sum, int& maxLength, int& maxSum) {
    if (root == NULL) {
        if (depth > maxLength) {  // If we finded a longer path, update maxLength and maxSum
            maxLength = depth;
            maxSum = sum;
        } else if (depth == maxLength) {  // If we finded a path with same length, update maxSum if sum is greater
            maxSum = max(maxSum, sum);
        }
        return; // Return when we reach the leaf node
    }

    sum = sum + root->data;  // Add the current node's data to the sum

    findLongestPathSum(root->left, depth + 1, sum, maxLength, maxSum);  // Depth will be increased by 1 as we are going to the next level
    findLongestPathSum(root->right, depth + 1, sum, maxLength, maxSum);
}

int sumOfLongestBloodline(Node* root) {
    int maxLength = 0;  // To store the maximum depth
    int maxSum = 0;  // To store the sum at max depth
    int sum = 0;  // To store the sum of the nodes on the path
    int depth = 0;  // To store the depth of the current node

    findLongestPathSum(root, depth, sum, maxLength, maxSum);  // Start from the root node with depth 0 and sum 0

    return maxSum;
}

// Function to create a sample tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->left->left = new Node(7);
    root->right->right = new Node(5);
    root->right->right->right = new Node(8);
    return root;
}

int main() {
    Node* root = createSampleTree();
    cout << "Sum of the longest bloodline of the tree: " << sumOfLongestBloodline(root) << endl;
    return 0;
}
// Time Complexity: O(N), where N is the number of nodes in the tree.
// Space Complexity: O(H), where H is the height of the tree.