// Write a function to convert Complete Binary Search Tree into Min Heap.

// Approach:
// 1. Perform an inorder traversal of the BST and store the elements in a vector. We'll get the elements in sorted order.
// 2. Pre-order Traversal to assign these values back to the tree nodes.
//    a.  Why pre-order? Because in a Min-Heap, parent comes before children.
//    b.  So we assign the smallest available value to the current node (root first), then go to left/right.

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
        left = right = nullptr;
    }
};

// Function to perform inorder traversal and store elements in a vector
void inorderTraversal(Node* root, vector<int>& elements) {
    if (root == nullptr) return;

    inorderTraversal(root->left, elements); // Traverse left subtree
    elements.push_back(root->data); // Store current node's data
    inorderTraversal(root->right, elements); // Traverse right subtree
}

// Function to perform pre-order traversal and assign values from the vector to the tree nodes
void assignValuesPreOrder(Node* root, vector<int>& elements, int& index) {
    if (root == nullptr) return;

    root->data = elements[index++]; // Assign the next value from the vector to the current node
    assignValuesPreOrder(root->left, elements, index); // Traverse left subtree
    assignValuesPreOrder(root->right, elements, index); // Traverse right subtree
}

// Function to convert BST into Min-Heap
void convertBSTtoMinHeap(Node* root) {
    vector<int> elements; // Vector to store elements of the BST
    inorderTraversal(root, elements); // Perform inorder traversal to get sorted elements

    int index = 0; // Index to track the position in the vector
    assignValuesPreOrder(root, elements, index); // Assign values back to the tree nodes using pre-order traversal
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(4);
  root->left = new Node(2);
  root->right = new Node(6);
  root->left->left = new Node(1);
  root->left->right = new Node(3);
  root->right->left = new Node(5);
  root->right->right = new Node(7);
  return root;
}

// Function to print Pre-Order traversal to verify min-Heap
void printPreOrder(Node* root) {
    if (root == nullptr) return;

    cout << root->data << " "; // Print current node's data
    printPreOrder(root->left); // Traverse left subtree
    printPreOrder(root->right); // Traverse right subtree
}

int main() {
    Node* root = createSampleBST(); // Create a sample BST

    cout << "Original BST (Pre-Order): ";
    printPreOrder(root); // Print original BST in pre-order
    cout << endl;

    convertBSTtoMinHeap(root); // Convert BST to Min-Heap

    cout << "Converted Min-Heap (Pre-Order): ";
    printPreOrder(root); // Print converted Min-Heap in pre-order
    cout << endl;

    return 0;
}

// Tree Structure:
//         4
//       /   \
//      2     6
//     / \   / \
//    1   3 5   7

// Converted Min-Heap:
//         1
//       /   \
//      2     3
//     / \   / \
//    4   5 6   7