// Write a function to find the path from root to a given node in a binary tree.
// This is important question because this can be used several places where we need to find a target node. So, if we have a path stored in vector to target node, we can use that path for various purposes like finding the lowest common ancestor, finding the distance between two nodes, etc.

// Notes : https://takeuforward.org/data-structure/print-root-to-node-path-in-a-binary-tree/

// Example :
//        1
//       / \
//      2   3
//         / \
//        4   5
//           /
//          6
// Given node = 6, the path from root to node 6 is: 1 -> 3 -> 5 -> 6

// Intiution:
// 1. We will use a recursive approach to find the path from root to the given node.
// 2. We will maintain a vector to store the path from root to the given node as we traverse the tree.
// 3. If we find the node, we will return true and print the path.
// 4. If we reach a leaf node and the node is not found, we will backtrack and remove the last element from the path vector.
// 5. The time complexity for this approach is O(n) where n is the number of nodes in the tree, as we may need to traverse all nodes in the worst case.
// 6. The space complexity for this approach is O(h) where h is the height of the tree, due to the recursive stack space and the path vector.

                            
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

// TreeNode structure
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    // Function to find the path from the
    // root to a given node with value 'x'
    bool getPath(TreeNode* root, vector<int>& arr, int x) {
        // Base case: If the current
        // node is null, return false
        if (!root) {
            return false;
        }

        // Add the current node's
        // value to the path vector
        // Add the current node at each step
        // to the path vector 'arr'
        arr.push_back(root->val);

        // If the current node's value is equal
        // to the target value 'x', return true
        if (root->val == x) {
            return true;
        }

        // Recursively search for the target value
        // 'x' in the left and right subtrees
        // If the target value 'x' is found in either
        // the left or right subtree, return true
        if (getPath(root->left, arr, x)
            || getPath(root->right, arr, x)) {
            return true;
        }

        // If the target value 'x' is not found
        // in the current path, backtrack
        arr.pop_back();
        return false;
    }

    // Function to find and return the path from
    // the root to a given node with value 'B'
    vector<int> solve(TreeNode* A, int B) {
        // Initialize an empty
        // vector to store the path
        vector<int> arr;

        // If the root node is null,
        // return the empty path vector
        if (A == NULL) {
            return arr;
        }

        // Call the getPath function to find
        // the path to the node with value 'B'
        getPath(A, arr, B);

        // Return the path vector
        return arr;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    Solution sol;

    int targetLeafValue = 7;

    vector<int> path = sol.solve(root, targetLeafValue);

    cout << "Path from root to leaf with value " <<
        targetLeafValue << ": ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }

    return 0;
}
                            
// Tree will look like this:
//        3
//       / \
//      5   1
//     / \ / \
//    6  2 0  8
//      /  \
//     7    4
// Given targetLeafValue = 7, the path from root to node 7 is: 3 -> 5 -> 2 -> 7
