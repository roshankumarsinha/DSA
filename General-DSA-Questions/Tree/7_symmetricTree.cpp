// Question 1 : Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

// =====================================================================================
// PROBLEM UNDERSTANDING
// =====================================================================================
//
// A tree is symmetric if the left subtree is a MIRROR REFLECTION of the right subtree.
//
// SYMMETRIC TREE:
//         1
//        / \
//       2   2
//      / \ / \
//     3  4 4  3
//
// NOT SYMMETRIC:
//         1
//        / \
//       2   2
//        \   \
//         3   3
//
// Mirror means:
// - Left child of left subtree = Right child of right subtree
// - Right child of left subtree = Left child of right subtree

// =====================================================================================
// APPROACH: Recursive Comparison of Mirror Nodes
// =====================================================================================
//
// INTUITION:
// -----------
// To check if a tree is symmetric, we need to compare two subtrees as mirrors.
// Two trees are mirrors of each other if:
//   1. Their root values are the same
//   2. Left subtree of tree1 is mirror of Right subtree of tree2
//   3. Right subtree of tree1 is mirror of Left subtree of tree2
//
// VISUAL EXPLANATION:
// -------------------
// For a symmetric tree:
//         1
//        / \
//       2   2      <- Compare: node 2 (left) with node 2 (right)
//      / \ / \
//     3  4 4  3    <- Compare: 3(left-left) with 3(right-right)
//                  <- Compare: 4(left-right) with 4(right-left)
//
// Think of folding the tree along the vertical axis through the root.
// For it to be symmetric, the folded halves should match perfectly.
//
// ALGORITHM:
// ----------
// 1. If root is NULL, tree is symmetric (empty tree)
// 2. Compare left and right subtrees using helper function isMirror(left, right)
// 3. isMirror(t1, t2):
//    - If both NULL, return true (both empty = mirror)
//    - If one NULL and other not, return false (structure mismatch)
//    - If values differ, return false
//    - Recursively check: isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left)
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack, h = height of tree
//
// RECURSION TREE for:
//         1
//        / \
//       2   2
//      / \ / \
//     3  4 4  3
//
//                    isSymmetric(1)
//                         |
//                 isMirror(2, 2)
//               /                 \
//      isMirror(3, 3)          isMirror(4, 4)
//       (left-left,              (left-right,
//        right-right)             right-left)
//        /        \               /        \
// isMirror(NULL,NULL) isMirror(NULL,NULL) isMirror(NULL,NULL) isMirror(NULL,NULL)
//      true           true               true               true
//         \           /                      \           /
//          \         /                        \         /
//           isMirror(3,3) = true               isMirror(4,4) = true
//                     \                       /
//                      \                     /
//                       isMirror(2,2) = true
//                              |
//                    isSymmetric(1) = true
//
// DETAILED TRACE:
// ---------------
// isMirror(node2_left, node2_right):
//   - Values match: 2 == 2 ✓
//   - Check isMirror(node2_left->left, node2_right->right) = isMirror(3, 3)
//     - Values match: 3 == 3 ✓
//     - isMirror(NULL, NULL) = true ✓
//     - isMirror(NULL, NULL) = true ✓
//     - Return true
//   - Check isMirror(node2_left->right, node2_right->left) = isMirror(4, 4)
//     - Values match: 4 == 4 ✓
//     - isMirror(NULL, NULL) = true ✓
//     - isMirror(NULL, NULL) = true ✓
//     - Return true
//   - Return true && true = true
//
// EXAMPLE OF NON-SYMMETRIC TREE:
// ------------------------------
//         1
//        / \
//       2   2
//        \   \
//         3   3
//
// isMirror(node2_left, node2_right):
//   - Values match: 2 == 2 ✓
//   - isMirror(NULL, 3) = false ❌  (left-left vs right-right: structure mismatch!)
//   - Return false

#include<iostream>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// =====================================================================================
// SOLUTION 1: Recursive Approach
// =====================================================================================

class Solution {
public:
    bool isMirror(TreeNode* t1, TreeNode* t2) {
        // Both empty - mirrors of each other
        if (t1 == NULL && t2 == NULL) return true;
        
        // One empty, one not - not mirrors
        if (t1 == NULL || t2 == NULL) return false;
        
        // Values must match, and subtrees must be mirrors
        return (t1->val == t2->val) 
            && isMirror(t1->left, t2->right)   // Left of t1 mirrors Right of t2
            && isMirror(t1->right, t2->left);  // Right of t1 mirrors Left of t2
    }

    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }
};

// =====================================================================================
// SOLUTION 2: Iterative Approach using Queue
// =====================================================================================
//
// INTUITION:
// -----------
// Instead of recursion, use a queue to compare nodes level by level.
// Push pairs of nodes that should be mirrors of each other.
//
// For each pair (t1, t2) we pop:
// - Check if values match
// - Push (t1->left, t2->right) and (t1->right, t2->left) for next comparison
//
// This is essentially BFS where we compare mirror positions.
//
// WHY USE QUEUE?
// --------------
// - Avoids recursion stack (useful for very deep trees)
// - Iterative solution is sometimes preferred in interviews
//
// Time Complexity: O(n)
// Space Complexity: O(n) - queue can hold up to n/2 nodes at the widest level

class SolutionIterative {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        
        while (!q.empty()) {
            TreeNode* t1 = q.front(); q.pop();
            TreeNode* t2 = q.front(); q.pop();
            
            // Both null - continue to next pair
            if (t1 == NULL && t2 == NULL) continue;
            
            // One null or values differ - not symmetric
            if (t1 == NULL || t2 == NULL) return false;
            if (t1->val != t2->val) return false;
            
            // Push children in mirror order
            q.push(t1->left);
            q.push(t2->right);
            q.push(t1->right);
            q.push(t2->left);
        }
        
        return true;
    }
};

// =====================================================================================
// VISUAL COMPARISON OF APPROACHES:
// =====================================================================================
//
// | Approach    | Time | Space  | Pros                  | Cons                    |
// |-------------|------|--------|----------------------|-------------------------|
// | Recursive   | O(n) | O(h)   | Clean, intuitive     | Stack overflow risk     |
// | Iterative   | O(n) | O(n)   | No stack overflow    | More code, less elegant |
//
// h = height of tree (O(log n) balanced, O(n) skewed)

// =====================================================================================
// EDGE CASES:
// =====================================================================================
//
// 1. Empty tree (NULL root) -> Symmetric ✓
// 2. Single node -> Symmetric ✓
// 3. Two nodes (root + one child) -> Not symmetric (unbalanced)
// 4. All same values but different structure -> Not symmetric

int main() {
    // Create symmetric tree:
    //         1
    //        / \
    //       2   2
    //      / \ / \
    //     3  4 4  3
    
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(3);

    Solution sol;
    SolutionIterative solIter;

    cout << "Tree 1 (Symmetric):" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   2" << endl;
    cout << "     / \\ / \\" << endl;
    cout << "    3  4 4  3" << endl;
    cout << "Recursive: " << (sol.isSymmetric(root1) ? "Symmetric" : "Not Symmetric") << endl;
    cout << "Iterative: " << (solIter.isSymmetric(root1) ? "Symmetric" : "Not Symmetric") << endl;

    // Create non-symmetric tree:
    //         1
    //        / \
    //       2   2
    //        \   \
    //         3   3
    
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->right = new TreeNode(3);
    root2->right->right = new TreeNode(3);

    cout << "\nTree 2 (Not Symmetric):" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   2" << endl;
    cout << "       \\   \\" << endl;
    cout << "        3   3" << endl;
    cout << "Recursive: " << (sol.isSymmetric(root2) ? "Symmetric" : "Not Symmetric") << endl;
    cout << "Iterative: " << (solIter.isSymmetric(root2) ? "Symmetric" : "Not Symmetric") << endl;

    return 0;
}

