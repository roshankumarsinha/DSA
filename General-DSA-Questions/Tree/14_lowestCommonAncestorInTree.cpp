// Write a function to find the lowest common ancestor of two nodes in a binary tree.

// Notes : https://takeuforward.org/data-structure/lowest-common-ancestor-for-two-given-nodes/

// The lowest common ancestor (LCA) of two nodes p and q in a binary tree is the lowest node that has both p and q as descendants.
// The Lowest Common Ancestor (LCA) of two nodes in a binary tree is the deepest node that has both nodes as descendants.
// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6
// LCA of 4 and 5 is 2.
// LCA of 5 and 6 is 1.
// LCA of 2 and 3 is 1.
// LCA of 4 and 6 is 1.

// Approach 1 :
// 1. Find the path from the root to node p and store it in a vector.
// 2. Find the path from the root to node q and store it in another vector.
// 3. Compare the two vectors and find the last common node in both vectors.
// 4. The last common node is the LCA of p and q.
// 5. The time complexity for this approach is O(n) where n is the number of nodes in the tree, as we may need to traverse all nodes in the worst case.

// Approach 2 :
// 1. Use a recursive approach to find the LCA.
// 2. If the current node is NULL, return NULL.
// 3. If the current node is equal to p or q, return the current node.
// 4. Recursively find the LCA in the left and right subtrees.
// 5. If both left and right subtrees return non-NULL values, the current node is the LCA.
// 6. If both left and right subtrees return NULL, return NULL.
// 7. If only one of the subtrees returns a non-NULL value, return that value. That means either p or q is found in that subtree.
// 8. The time complexity for this approach is O(n) where n is the number of nodes in the tree, as we may need to traverse all nodes in the worst case.
// 9. The space complexity for this approach is O(h) where h is the height of the tree, due to the recursive stack space.

// Approach 2 is more efficient as it avoids storing paths and directly finds the LCA in a single traversal of the tree.

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    Node* findLCA(Node* root, int n1, int n2) {
        // Base case: If root is NULL, return NULL
        if (root == nullptr)
            return nullptr;

        // If either n1 or n2 matches root's data, return root
        // This means we have found one of the nodes we are looking for
        if (root->data == n1 || root->data == n2)
            return root;

        // Recur for left and right subtrees
        Node* leftLCA = findLCA(root->left, n1, n2);
        Node* rightLCA = findLCA(root->right, n1, n2);

        // If both sides return non-null, current node is LCA
        // This means both n1 and n2 are found in different subtrees of the current node
        if (leftLCA && rightLCA)
            return root;

        // Otherwise, return the non-null side
        // If one side is null, it means both n1 and n2 are in the other subtree
        // If both sides are null, it means neither n1 nor n2 is present in the tree rooted at this node
        return (leftLCA != nullptr) ? leftLCA : rightLCA;   // This line returns the non-null child if one exists, or null if both are null. So this line do 2 things:
        // 1. If leftLCA is not null, it means n1 or n2 is found in the left subtree, so we return leftLCA.
        // 2. If rightLCA is not null, it means n1 or n2 is found in the right subtree, so we return rightLCA.
        // 3. If both leftLCA and rightLCA are null, it means neither n1 nor n2 is found in the tree rooted at this node, so we return null.
    }
};

int main() {
    /*
            1
           / \
          2   3
         / \ / \
        4  5 6  7
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;

    int n1 = 4, n2 = 5;
    Node* lca = sol.findLCA(root, n1, n2);
    if (lca)
        cout << "LCA of " << n1 << " and " << n2 << " is: " << lca->data << endl;

    n1 = 4, n2 = 6;
    lca = sol.findLCA(root, n1, n2);
    if (lca)
        cout << "LCA of " << n1 << " and " << n2 << " is: " << lca->data << endl;

    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
