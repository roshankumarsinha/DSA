// Write a function to find the lowest common ancestor of two nodes in a binary tree.
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

// Approach:
// 1. If the root is NULL, return NULL.
// 2. If the root is equal to p or q, return the root.
// 3. Recursively find the LCA in the left subtree.
// 4. Recursively find the LCA in the right subtree.
// 5. If both left and right subtrees return a non-NULL value, it means that p and q are present in different subtrees, and the current node is the LCA.
// 6. If only one of the left or right subtree returns a non-NULL value, it means that p and q are present in the same subtree, and the non-NULL value is the LCA.
// 7. If both left and right subtrees return NULL, it means that p and q are not present in the tree, and return NULL.
// 8. The time complexity for this approach is O(n) because we are traversing each node only once.
// 9. The space complexity for this approach is O(n) because of the recursive stack space.

// The basic approach is if we got both non-null value from left and right subtree then that is the LCA and for other case either pass Null or the founded node to the parent node.

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

// Function to find the lowest common ancestor of two nodes in a binary tree
Node* lowestCommonAncestor(Node* root, int p, int q) {

    if (root == NULL) {   // If the root is NULL, return NULL
        return NULL;
    }

    if (root->data == p || root->data == q) {   // If the root is equal to p or q, return the root to the parent node
        return root;
    }

    Node* left = lowestCommonAncestor(root->left, p, q);  // Recursively find the LCA in the left subtree
    Node* right = lowestCommonAncestor(root->right, p, q);  // Recursively find the LCA in the right subtree

    if (left != NULL && right != NULL) {  // If both left and right subtrees return a non-NULL value, it means that p and q are present in different subtrees, and the current node is the LCA
        return root;
    }

    else if (left != NULL && right == NULL) {  // If only one of the left or right subtree returns a non-NULL value, it means that p and q are present in the same subtree, and the non-NULL value is the LCA
        return left;
    }

    else if (left == NULL && right != NULL) {  // If only one of the left or right subtree returns a non-NULL value, it means that p and q are present in the same subtree, and the non-NULL value is the LCA
        return right;
    }

    else {  // If both left and right subtrees return NULL, it means that p and q are not present in the tree, and return NULL
        return NULL;
    }
}

// Function to create a sample tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    return root;
}

int main() {
    Node* root = createSampleTree();
    int p = 4, q = 5;
    Node* result = lowestCommonAncestor(root, p, q);
    if (result != NULL) {
        cout << "Lowest Common Ancestor of " << p << " and " << q << " is " << result->data << endl;
    } else {
        cout << "Lowest Common Ancestor of " << p << " and " << q << " is NULL" << endl;
    }
    return 0;
}