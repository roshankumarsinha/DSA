// Write a function to do Morris Traversal of a binary tree.
// Morris Traversal is an efficient in-place tree traversal technique that does not use recursion or extra space (like a stack or queue).
// It modifies the tree temporarily to establish threaded binary links for traversal.

// Why Morris Traversal?
//  1. ✅ No extra space (O(1) auxiliary space, unlike recursion or stack-based traversal).
//  2. ✅ Efficient O(N) time complexity.

// https://takeuforward.org/data-structure/morris-preorder-traversal-of-a-binary-tree/ -> Follow this link for pre-order Morris Traversal
// https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/ -> Follow this link for in-order Morris Traversal
// https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/ -> Follow this link for flattening a binary tree to a linked list

// Approach for Inorder Traversal Using Morris Traversal :-
//  Step 1: Initialize the current node as the root.
//  Step 2: If the current node has no left child:
//    a.  Print the current node.
//    b.  Move to the right child.
//  Step 3: If the current node has a left child:
//    a.  Find the rightmost node (inorder predecessor) of the left subtree.
//    b.  If the rightmost node’s right is NULL:
//      b1. Set its right to the current node (temporary thread).
//      b2. Move to the left child.
//    c.  If the rightmost node’s right is the current node: (Means we have already created a thread and we are backtracking)
//      c1. Restore the tree (remove the thread).
//      c2. Print the current node. (This is the key difference from preorder traversal. In inorder, we print after restoring the tree but in preorder, we print before creating the thread.)
//      c3. Move to the right child.
//  Step 4: Repeat until all nodes are visited.
 
// Approach for Preorder Traversal Using Morris Traversal :- (Similar to inorder Morris traversal, but we print the node before moving to the left subtree.)
//  Step 1: If the node has no left child, print it and move to the right.
//  Step 2: If the node has a left child:
//    a.  Find its inorder predecessor.
//    b.  If the right pointer of the predecessor is NULL:
//      b1. Print the current node (before creating the thread).
//      b2. Make a thread to the current node.
//      b3. Move to the left.
//    c.  If the right pointer is already pointing to the current node:
//      c1. Remove the thread.
//      c2. Move to the right.


// Inorder Morris Traversal Implementation
// Inorder first prints the left subtree, then the current node, and finally the right subtree. So, when there is a case if you want to visit left child first, then print the current node, and then visit the right child, you can use Inorder Traversal.
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>

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
    // Function to perform iterative Morris
    // inorder traversal of a binary tree
    vector<int> getInorder(TreeNode* root) {
        // Vector to store the
        // inorder traversal result
        vector<int> inorder;
        // Pointer to the current node,
        // starting from the root
        TreeNode* cur = root;
        
        // Loop until the current
        // node is not NULL
        while (cur != NULL) {
            // If the current node's
            // left child is NULL
            if (cur->left == NULL) {
                // Add the value of the current
                // node to the inorder vector
                inorder.push_back(cur->val);
                // Move to the right child
                cur = cur->right;
            } else {
                // If the left child is not NULL,
                // find the predecessor (rightmost node
                // in the left subtree)
                TreeNode* prev = cur->left;
                while (prev->right && prev->right != cur) {   // Traverse to the rightmost node
                    prev = prev->right;
                }
                
                // If the predecessor's right child
                // is NULL, establish a temporary link
                // and move to the left child
                if (prev->right == NULL) {
                    prev->right = cur;
                    // preorder.push_back(cur->val);    // This line will be added if you want to do preorder traversal, since in preorder we print the current node before moving to the left child
                                                        // and first thing printed in preorder is root(current node) and then we move to the left child
                    // Move to the left child
                    cur = cur->left;
                } else {
                    // If the predecessor's right child
                    // is already linked, remove the link,
                    // add current node to inorder vector,
                    // and move to the right child, so if there is a thread already present,
                    // that means we have already visited the left subtree and now we can print root(current node)
                    // and move to the right child(or right subtree)
                    prev->right = NULL;
                    inorder.push_back(cur->val);    // This line will be removed if you want to do preorder traversal
                    cur = cur->right;
                }
            }
        }
        
        // Return the inorder
        // traversal result
        return inorder;
    }
};


int main() {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->right = new TreeNode(6);

    Solution sol;
    
    vector<int> inorder = sol.getInorder(root);

    cout << "Binary Tree Morris Inorder Traversal: ";
    for(int i = 0; i< inorder.size(); i++){
        cout << inorder[i] << " ";
    }
    cout << endl;

    return 0;
}
 