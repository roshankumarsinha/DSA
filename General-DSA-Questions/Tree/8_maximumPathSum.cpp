// Maximum Sum Path in Binary Tree
// You are given a binary tree (nodes can have positive or negative values). A path means:
// You can start at any node
// You can end at any node
// You can move only parent → child connections
// Path must be continuous
// You cannot reuse a node
// Your task:
// 👉 Find the maximum possible sum of values of any such path.

// Chatgpt Notes : https://chatgpt.com/share/695fcde7-7518-8006-a98a-f16fc68c038e
// TUF Notes : https://takeuforward.org/data-structure/maximum-sum-path-in-binary-tree

// Example : Tree considered here is :
//       -10
//       /  \
//      9   20
//          / \
//         15  7
// Maximum Path Sum = 15 + 20 + 7 = 42

// Intiution:
// 🔍 Key Observation
// At any node, 4 types of paths are possible:
//        X
//       / \
//      L   R
// Possible paths using X:
// 1.  X alone
// 2. X + left subtree
// 3. X + right subtree
// 4. Left + X + Right ← (this is a "full turn" path)

// But ⚠️ Only one side can be passed upward to parent,
// because parent can continue path only in one direction.
// So:
// Case 4 can be the final answer, but cannot be passed upward.
// Only case 1,2,3 are returned upward.
// For every node Compute:
// 1. Best downward path starting from this node.
// 2. Also update the global maximum considering full turn path.
// ✨ Important Trick
// If a child gives negative contribution → ignore it (use 0 instead)
// Because negative reduces the sum.
// 🔄 What We Compute at Each Node. 
// Let:
//     left = max(0, best downward path from left)
//     right = max(0, best downward path from right)

// Then:
//     Best path passing through this node
//     left + node->val + right
// Update global answer with this.
// node->val + max(left, right)
// Return this value upward.

#include <iostream>
#include <climits>
using namespace std;

// Definition for a binary tree node.
class TreeNode {
  public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxSum = INT_MIN;   // Stores final answer

    // Returns maximum downward path sum starting from this node
    int dfs(TreeNode* root) {
        // Base Case
        if(root == NULL) return 0;

        // Step 1: Get best contributions from left & right
        int left = max(0, dfs(root->left)); // Ignore negative contributions, use 0 instead, calculate best downward path from left
        int right = max(0, dfs(root->right)); // Ignore negative contributions, use 0 instead, calculate best downward path from right

        // Step 2: Best path passing through current node
        int currentPath = left + root->val + right;

        // Step 3: Update global answer
        maxSum = max(maxSum, currentPath);

        // Step 4: Return best single-side path to parent
        return root->val + max(left, right);
    }

    int maxPathSum(TreeNode* root) {
        dfs(root);
        return maxSum;
    }
};

// Function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    Solution sol;
    cout << "Maximum Path Sum: " << sol.maxPathSum(root) << endl; // Output: 42
    return 0;
}

