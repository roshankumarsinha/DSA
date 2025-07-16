// Write a function to construct a Binary Search Tree (BST) from a given preorder traversal.

// Video from Striver: https://www.youtube.com/watch?v=UmJT3j26t1I

// Approach 1:
// 1. Sort the preorder array and this will give us the inorder traversal of the BST.
// 2. We can construct any tree from inorder and preorder traversal.
// 3. Time Complexity: O(NlogN) for sorting + O(N) for constructing the tree = O(NlogN).
// 4. Space Complexity: O(N) for storing the inorder traversal.

// Approach 2:
// 1. Use upper and lower bounds to find the position of the current node in the preorder array.
// 2. Each recursive call ensures: lower < node->data < upper.
// 3. If the current node's value is within the bounds, create a new node and recursively construct the left and right subtrees.
// 4. Time Complexity: O(N) for constructing the tree.
// 5. Space Complexity: O(N) for storing the nodes in the stack during recursion.

// It's not necessary to take lower bound as it is optional, we can work with just upper bound as well.

// Intiution:
// 1. The first element of the preorder traversal is always the root of the BST.
// 2. The elements that come after the root in the preorder traversal can be divided into two parts: those that are less than the root (left subtree) and those that are greater than the root (right subtree).
// 3. We can recursively apply this logic to construct the left and right subtrees until we have processed all elements in the preorder traversal.

#include <iostream>
#include <vector>
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

// Function to construct a BST from preorder traversal using upper and lower bounds
Node* constructBSTFromPreorder(vector<int>& preorder, int& index, int lower, int upper) {  // preorder is the array of preorder traversal, index is the current index in the array, lower and upper are the bounds for the current node's value
    
    if (index >= preorder.size()) { // If the index is greater than or equal to the size of the preorder array, return NULL
        return NULL;
    }

    if (preorder[index] < lower || preorder[index] > upper) {
        return NULL;  // If the current value is out of bounds, return NULL
    }

    // If the current value is within bounds, increment the index
    // Create a new node with the current value
    Node* root = new Node(preorder[index++]);

    // Recursively construct the left and right subtrees
    root->left = constructBSTFromPreorder(preorder, index, lower, root->data);
    root->right = constructBSTFromPreorder(preorder, index, root->data, upper);

    return root;
}

// Function to construct a BST from preorder traversal
Node* constructBSTFromPreorderMain(vector<int>& preorder) {
    int index = 0;  // Initialize the index to 0
    return constructBSTFromPreorder(preorder, index, INT_MIN, INT_MAX);  // Call the helper function with initial bounds
}

// Function to perform inorder traversal of the BST
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;  // If the root is NULL, return
    }
    inorderTraversal(root->left);  // Traverse the left subtree
    cout << root->data << " ";  // Print the current node's value
    inorderTraversal(root->right);  // Traverse the right subtree
}

// Function to create a sample BST from preorder traversal
Node* createSampleBST() {
    vector<int> preorder = {10, 5, 1, 7, 40, 50};  // Sample preorder traversal
    return constructBSTFromPreorderMain(preorder);  // Construct the BST from the preorder traversal
}

int main() {
    Node* root = createSampleBST();  // Create a sample BST from preorder traversal

    cout << "Inorder Traversal of the constructed BST: ";
    inorderTraversal(root);  // Perform inorder traversal of the constructed BST
    cout << endl;

    return 0;
}

// Example Output:
// Inorder Traversal of the constructed BST: 1 5 7 10 40 50
// Tree Structure:
//         10
//        /  \
//       5    40
//      / \     \
//     1   7    50
