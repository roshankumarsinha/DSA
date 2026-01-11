// Write a function to find maximum sum of nodes in Binary tree such that no two nodes are adjacent to each other.
// It means that if we select root node, we cannot select direct children of root node and if we select any child of root node, we cannot select their direct children and root node.

// Video link : https://www.youtube.com/watch?v=S68tDCB4mTY

// =====================================================================================
// PROBLEM UNDERSTANDING
// =====================================================================================
//
// Given a binary tree, find the maximum sum of nodes such that NO TWO SELECTED NODES
// are directly connected (parent-child relationship).
//
// Example Tree:
//         1
//        / \
//       2   3
//      /   / \
//     1   4   5
//
// Option 1: Select 1 (root) + 1 + 4 + 5 = 11 (can't select 2,3 as they're children of 1)
// Option 2: Select 2 + 3 = 5 (can't select 1,1,4,5 as they're adjacent to 2 or 3)
// Wait, let's reconsider...
// If we select 2, we can't select 1(root) or 1(left child of 2)
// If we select 3, we can't select 1(root), 4, or 5
//
// Better analysis:
// - Select root(1): Can't select 2,3. Can select grandchildren: 1,4,5
//   Sum = 1 + 1 + 4 + 5 = 11
// - Don't select root(1): Can select 2 and/or 3
//   If select 2: Can't select its child 1. Sum from 2's subtree = 2
//   If select 3: Can't select 4,5. Sum from 3's subtree = 3
//   Or don't select 2: Can select 1. Sum = 1
//   Or don't select 3: Can select 4+5. Sum = 9
//   Best: 2 + 4 + 5 + 1 = 12? Wait, 2 and 1(child of 2) are adjacent...
//   
// Let me re-trace:
// - Select root(1): Get 1 + maxSum(grandchildren) = 1 + maxSum(1) + maxSum(4) + maxSum(5)
// - Don't select root: Get maxSum(2) + maxSum(3)
//
// This is the classic "House Robber III" problem!

// =====================================================================================
// APPROACH 1: Pure Recursion (Brute Force) - O(2^n) Time Complexity
// =====================================================================================
//
// INTUITION:
// -----------
// For each node, we have TWO choices:
//   1. INCLUDE this node: Add its value, but SKIP its children (go to grandchildren)
//   2. EXCLUDE this node: Don't add its value, consider children normally
//
// The answer is the maximum of these two choices.
//
// WHY O(2^n) TIME COMPLEXITY?
// ---------------------------
// When we INCLUDE a node, we call recursion on its grandchildren (4 calls potentially).
// When we EXCLUDE a node, we call recursion on its children (2 calls).
// This leads to overlapping subproblems - same nodes are visited multiple times!
//
// Example: For node X, when we EXCLUDE X and INCLUDE its child Y, we compute
// grandchildren of Y. But when we INCLUDE X, we also compute grandchildren of X
// which overlap with grandchildren of Y. This causes exponential calls.
//
// RECURSION FORMULA:
// ------------------
// For each node:
//   include = node->val + solve(node->left->left) + solve(node->left->right)
//                       + solve(node->right->left) + solve(node->right->right)
//   exclude = solve(node->left) + solve(node->right)
//   return max(include, exclude)
//
// RECURSION TREE for:
//         1
//        / \
//       2   3
//      /
//     4
//
//                          solve(1)
//                         /        \
//              Include 1              Exclude 1
//     1 + solve(4) + solve(NULL)      solve(2) + solve(3)
//         + solve(NULL) + solve(NULL)     |          |
//              |                     solve(2)    solve(3)
//          solve(4)                 /      \        |
//          /     \           Include 2  Exclude 2  Include 3
//     Include 4  Exclude 4      ...        ...       ...
//        |          |
//       4+0        0
//
// Notice: solve(2), solve(3), solve(4) may be called MULTIPLE times!
// This is why we need memoization.

#include<iostream>
#include<unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// =====================================================================================
// SOLUTION 1: Pure Recursion - O(2^n) Time, O(h) Space (recursion stack)
// =====================================================================================

class SolutionBruteForce {
public:
    int solve(TreeNode* root) {
        if (root == NULL) return 0;

        // Option 1: INCLUDE this node
        // Add current node's value + sum from grandchildren (skip children)
        int include = root->val;
        
        if (root->left) {
            include += solve(root->left->left);
            include += solve(root->left->right);
        }
        if (root->right) {
            include += solve(root->right->left);
            include += solve(root->right->right);
        }

        // Option 2: EXCLUDE this node
        // Don't add current value, consider children normally
        int exclude = solve(root->left) + solve(root->right);

        return max(include, exclude);
    }

    int maxSum(TreeNode* root) {
        return solve(root);
    }
};

// =====================================================================================
// APPROACH 2: Recursion with Memoization (Top-Down DP) - O(n) Time
// =====================================================================================
//
// INTUITION:
// -----------
// The brute force solution has overlapping subproblems - we compute the same
// nodes multiple times. We can use a hash map to store results for each node.
//
// WHY DOES MEMOIZATION HELP?
// --------------------------
// Each node is computed at most once. After that, we just look up the result.
// Since there are n nodes, we do O(n) computations.
//
// HOW TO MEMOIZE?
// ---------------
// Use unordered_map<TreeNode*, int> where:
// - Key: pointer to the node
// - Value: maximum sum for subtree rooted at that node
//
// Before computing, check if result exists in map. If yes, return it.
// After computing, store the result in map.
//
// RECURSION TREE WITH MEMOIZATION:
// --------------------------------
// Same tree as before, but now:
//
//                          solve(1) [compute]
//                         /        \
//              Include 1              Exclude 1
//     1 + solve(4)[compute]           solve(2)[compute] + solve(3)[compute]
//         + solve(NULL)                    |                    |
//              |                      (includes solve(4)   (already computed
//          solve(4)                    but solve(4) is      from Include 1)
//          CACHED!                     already CACHED!)
//
// Each node is computed exactly ONCE, then cached.
//
// Time Complexity: O(n) - each node visited once
// Space Complexity: O(n) - for memoization map + O(h) for recursion stack

class SolutionMemoization {
public:
    unordered_map<TreeNode*, int> memo;

    int solve(TreeNode* root) {
        if (root == NULL) return 0;

        // Check if already computed
        if (memo[root]) {
            return memo[root];
        }

        // Option 1: INCLUDE this node
        int include = root->val;
        
        if (root->left) {
            include += solve(root->left->left);
            include += solve(root->left->right);
        }
        if (root->right) {
            include += solve(root->right->left);
            include += solve(root->right->right);
        }

        // Option 2: EXCLUDE this node
        int exclude = solve(root->left) + solve(root->right);

        // Store result and return
        memo[root] = max(include, exclude);
        return memo[root];
    }

    int maxSum(TreeNode* root) {
        memo.clear();
        return solve(root);
    }
};

// =====================================================================================
// APPROACH 3: Optimized DP with Pair (Best Approach) - O(n) Time, O(h) Space
// =====================================================================================
//
// INTUITION:
// -----------
// Instead of storing results in a map, we can return TWO values from each call:
//   1. Maximum sum if we INCLUDE this node
//   2. Maximum sum if we EXCLUDE this node
//
// This way, the parent can directly use these values without recomputation.
//
// WHY IS THIS BETTER?
// -------------------
// - No hash map overhead (no hashing, no memory allocation for map)
// - Cleaner logic - each node returns exactly what its parent needs
// - Space is O(h) for recursion stack only, no extra O(n) for map
//
// RECURSION FORMULA:
// ------------------
// For each node, return pair<include, exclude>:
//   
//   leftPair = solve(node->left)   // {include_left, exclude_left}
//   rightPair = solve(node->right) // {include_right, exclude_right}
//   
//   // If we INCLUDE this node, children must be EXCLUDED
//   include = node->val + leftPair.second + rightPair.second
//   
//   // If we EXCLUDE this node, children can be either included or excluded
//   // Take the best option for each child
//   exclude = max(leftPair.first, leftPair.second) 
//           + max(rightPair.first, rightPair.second)
//   
//   return {include, exclude}
//
// Final answer: max(root_include, root_exclude)
//
// RECURSION TREE for:
//         1
//        / \
//       2   3
//      /
//     4
//
//                    solve(1)
//                   /        \
//             solve(2)      solve(3)
//              /    \          |
//         solve(4)  NULL      NULL
//          /    \
//        NULL   NULL
//
// Bottom-up computation:
// solve(4) = {include=4, exclude=0}
// solve(2) = {include=2+0=2, exclude=max(4,0)=4}
// solve(3) = {include=3, exclude=0}
// solve(1) = {include=1+4+0=5, exclude=max(2,4)+max(3,0)=4+3=7}
//
// Answer = max(5, 7) = 7
//
// Wait, let me recalculate:
// For node 2: children are 4 and NULL
//   leftPair = {4, 0}, rightPair = {0, 0}
//   include = 2 + 0 + 0 = 2  (if we include 2, we must exclude children)
//   exclude = max(4,0) + max(0,0) = 4 (if we exclude 2, best option for left child is 4)
//   return {2, 4}
//
// For node 3: children are NULL and NULL
//   return {3, 0}
//
// For node 1: children are 2 and 3
//   leftPair = {2, 4}, rightPair = {3, 0}
//   include = 1 + 4 + 0 = 5 (include 1, must exclude 2 and 3)
//   exclude = max(2,4) + max(3,0) = 4 + 3 = 7
//   return {5, 7}
//
// Answer = max(5, 7) = 7 (achieved by excluding root, taking max from children)
// Path: exclude 1 -> exclude 2 (take 4) -> include 4 + include 3 = 4 + 3 = 7

class SolutionOptimized {
public:
    // Returns {include, exclude} for each node
    pair<int, int> solve(TreeNode* root) {
        if (root == NULL) {
            return {0, 0};
        }

        pair<int, int> leftPair = solve(root->left);
        pair<int, int> rightPair = solve(root->right);

        // If we INCLUDE this node, we must EXCLUDE both children
        int include = root->val + leftPair.second + rightPair.second;

        // If we EXCLUDE this node, take the best option for each child
        int exclude = max(leftPair.first, leftPair.second) 
                    + max(rightPair.first, rightPair.second);

        return {include, exclude};
    }

    int maxSum(TreeNode* root) {
        pair<int, int> result = solve(root);
        return max(result.first, result.second);
    }
};

// =====================================================================================
// DETAILED TRACE for Tree:
//         10
//        /  \
//       1    2
//      / \
//     3   4
//
// solve(3) = {3, 0}
// solve(4) = {4, 0}
// solve(1): left={3,0}, right={4,0}
//   include = 1 + 0 + 0 = 1
//   exclude = max(3,0) + max(4,0) = 3 + 4 = 7
//   return {1, 7}
//
// solve(2) = {2, 0}
//
// solve(10): left={1,7}, right={2,0}
//   include = 10 + 7 + 0 = 17 (include 10, exclude 1 and 2)
//   exclude = max(1,7) + max(2,0) = 7 + 2 = 9
//   return {17, 9}
//
// Answer = max(17, 9) = 17
// Selected nodes: 10 (root) + 3 + 4 = 17
// =====================================================================================

// =====================================================================================
// COMPARISON OF APPROACHES:
// =====================================================================================
//
// | Approach          | Time Complexity | Space Complexity | Notes                    |
// |-------------------|-----------------|------------------|--------------------------|
// | Brute Force       | O(2^n)          | O(h)             | Exponential, TLE         |
// | Memoization       | O(n)            | O(n) + O(h)      | HashMap overhead         |
// | Optimized (Pair)  | O(n)            | O(h)             | Best approach, no extra  |
//
// h = height of tree (O(log n) for balanced, O(n) for skewed)

// =====================================================================================
// SIMILAR PROBLEMS:
// =====================================================================================
//
// 1. House Robber (Array version): Same concept but on linear array
// 2. House Robber II: Circular array version
// 3. House Robber III: This problem (tree version)
// 4. Maximum sum of non-adjacent elements in array

int main() {
    // Create test tree:
    //         10
    //        /  \
    //       1    2
    //      / \
    //     3   4
    
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    SolutionBruteForce sol1;
    SolutionMemoization sol2;
    SolutionOptimized sol3;

    cout << "Tree structure:" << endl;
    cout << "        10" << endl;
    cout << "       /  \\" << endl;
    cout << "      1    2" << endl;
    cout << "     / \\" << endl;
    cout << "    3   4" << endl;
    cout << endl;

    cout << "Brute Force: " << sol1.maxSum(root) << endl;
    cout << "Memoization: " << sol2.maxSum(root) << endl;
    cout << "Optimized:   " << sol3.maxSum(root) << endl;
    cout << endl;
    cout << "Expected: 17 (select 10 + 3 + 4)" << endl;

    // Test another tree
    //         1
    //        / \
    //       2   3
    //        \   \
    //         4   5
    
    cout << "\n--- Second Test ---" << endl;
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->right = new TreeNode(4);
    root2->right->right = new TreeNode(5);

    cout << "Tree: 1 -> (2 -> 4), (3 -> 5)" << endl;
    cout << "Optimized: " << sol3.maxSum(root2) << endl;
    cout << "Expected: 4 + 5 = 9 (grandchildren of root)" << endl;

    return 0;
}
