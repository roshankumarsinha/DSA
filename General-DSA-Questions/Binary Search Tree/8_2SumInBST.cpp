// Write a function to determine whether two nodes exist in the tree such that their sum equals a given target.

// ✅ Problem Statement
// Given the root of a BST and an integer k, return true if there exist two elements in the BST such that their sum is equal to k,
// else return false.

// Approach 1: Inorder Traversal + Two Pointers
// 1. Perform an inorder traversal of the BST and store the elements in a vector. The inorder traversal of a BST gives us a sorted array.
// 2. Use two pointers, one starting from the beginning of the array and the other from the end.
// 3. If the sum of the elements at the two pointers is equal to k, return true.
// 4. If the sum is less than k, move the left pointer to the right (increase the sum).
// 5. If the sum is greater than k, move the right pointer to the left (decrease the sum).
// 6. Repeat steps 3-5 until the two pointers meet.
// 7. If no such pair is found, return false.
// 8. Time Complexity: O(N) for the inorder traversal and O(N) for the two-pointer approach, resulting in O(N) overall.
// 9. Space Complexity: O(N) for storing the elements in the vector.

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

// Function to perform inorder traversal and store elements in a vector
void inorderTraversal(Node* root, vector<int>& elements) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, elements);
    elements.push_back(root->data);
    inorderTraversal(root->right, elements);
}

// Function to check if there exist two elements in the BST such that their sum equals k
bool findTarget(Node* root, int k) {
    vector<int> elements;
    inorderTraversal(root, elements); // Perform inorder traversal to get sorted elements

    int left = 0; // Pointer starting from the beginning of the array
    int right = elements.size() - 1; // Pointer starting from the end of the array

    while (left < right) {
        int sum = elements[left] + elements[right];
        if (sum == k) {
            return true; // Found a pair with the required sum
        } else if (sum < k) {
            left++; // Move left pointer to the right to increase the sum
        } else {
            right--; // Move right pointer to the left to decrease the sum
        }
    }
    return false; // No such pair found
}

// Function to create a sample BST
Node* createSampleTree() {
  Node* root = new Node(5);
  root->left = new Node(3);
  root->right = new Node(6);
  root->left->left = new Node(2);
  root->left->right = new Node(4);
  root->right->right = new Node(7);
  return root;
}

int main() {
    Node* root = createSampleTree();
    int k = 9; // Target sum
    if (findTarget(root, k)) {
        cout << "There exist two elements in the BST such that their sum equals " << k << endl;
    } else {
        cout << "No such pair found in the BST." << endl;
    }
    return 0;
}

// Tree Structure:
//        5
//       / \
//      3   6
//     / \   \
//    2   4   7

// Example: For k = 9, the pair (3, 6) exists in the BST, so the output will be:
// "There exist two elements in the BST such that their sum equals 9"

// If we want to optimize space complexity, we can use Two Iterators (Inorder + Reverse Inorder)
// Approach 2: Two Iterators (Inorder + Reverse Inorder)
// 1. Use two iterators to traverse the BST in inorder and reverse inorder.
// 2. The inorder iterator will give us the smallest element, and the reverse inorder iterator will give us the largest element.
// 3. These simulate the two-pointer approach without using extra space for storing elements.
// Study this approach from Youtube or ChatGPT.
// 4. Time Complexity: O(N) for the inorder traversal and O(N) for the two-pointer approach, resulting in O(N) overall.
// 5. Space Complexity: O(H) for the stack space used in the recursion, where H is the height of the BST.