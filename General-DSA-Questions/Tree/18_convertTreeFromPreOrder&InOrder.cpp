// Convert a binary tree from its preorder and inorder traversal arrays.

// Problem Statement: Given the Preorder and Inorder traversal of a Binary Tree, construct the Unique Binary Tree represented by them.

// Example:
// Inorder: [40, 20, 50, 10, 60, 30]
// Preorder: [10, 20, 40, 50, 30, 60]
// The constructed tree will be:
//         10
//       /    \
//      20     30
//     / \      \
//    40  50    60

// Video link : https://www.youtube.com/watch?v=aZNaLrVebKQ
// Notes link : https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/


// Approach:
// 1. The first element of the preorder array is always the root of the tree.
// 2. Find the index of this root in the inorder array :
//    a. We can use a map to store the index of each element in the inorder array for O(1) lookup.
// 3. Split the inorder array into left and right subtrees using the index of the root.
// 4. Recursively construct the left and right subtrees using the corresponding segments of the preorder and inorder arrays.
// 5. Return the constructed tree.
// 6. We wil use variables inStart, inEnd, preStart, preEnd to keep track of the current segments of the inorder and preorder arrays being processed.


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Helper function to build the tree recursively
// This function constructs the tree from the given segments of inorder and preorder arrays
// inStart and inEnd are the indices for the inorder segment
// preStart and preEnd are the indices for the preorder segment
// inIndexMap{value, index} is a map to quickly find the index of any value in the inorder array
Node* buildTreeHelper(const vector<int>& inorder, const vector<int>& preorder,
                      int inStart, int inEnd, int preStart, int preEnd,
                      unordered_map<int, int>& inIndexMap) {

    // Base case: if the current segment is invalid
    if (inStart > inEnd || preStart > preEnd) {
        return nullptr;
    }

    // The first element of the preorder segment is the root
    int rootValue = preorder[preStart];
    Node* root = new Node(rootValue);
    
    // Find the index of the root in the inorder array
    int rootIndex = inIndexMap[rootValue];

    // Calculate the size of the left subtree
    int leftSize = rootIndex - inStart;
    
    // Recursively build the left and right subtrees
    // Left subtree:
    //  inStart will remain the same, inEnd will be rootIndex - 1
    //  preStart will be preStart + 1, preEnd will be preStart + leftSize
    //  Note: preStart + 1 is the next element in preorder after the root
    //  Note: preStart + leftSize is the last element in preorder for the left subtree
    root->left = buildTreeHelper(inorder, preorder, inStart, rootIndex - 1,
                                  preStart + 1, preStart + leftSize,
                                  inIndexMap);

    // Right subtree:
    //  inStart will be rootIndex + 1, inEnd will remain the same
    //  preStart will be preStart + leftSize + 1, preEnd will be preEnd
    //  Note: preStart + leftSize + 1 is the next element in preorder after the left subtree
    root->right = buildTreeHelper(inorder, preorder, rootIndex + 1, inEnd,
                                   preStart + leftSize + 1, preEnd,
                                   inIndexMap);

    return root; // Return the constructed subtree
}

Node* buildTree(const vector<int>& inorder, const vector<int>& preorder) {
    // Create a map to store the index of each element in the inorder array
    unordered_map<int, int> inIndexMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inIndexMap[inorder[i]] = i; // Store the index of each element
    }

    // Call the helper function to build the tree
    return buildTreeHelper(inorder, preorder, 0, inorder.size() - 1,
                           0, preorder.size() - 1, inIndexMap);
}

// Function to print the tree in inorder (for testing)
void printInOrder(Node* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

int main() {
    vector<int> inorder = {40, 20, 50, 10, 60, 30};
    vector<int> preorder = {10, 20, 40, 50, 30, 60};

    Node* root = buildTree(inorder, preorder);

    cout << "Inorder traversal of the constructed tree: ";
    printInOrder(root); // Output should be the inorder traversal of the constructed tree
    cout << endl;

    return 0;
}