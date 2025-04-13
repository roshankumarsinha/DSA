// Write a function to find largest BST in a binary tree.

// The size of a BST is the number of nodes in the BST.
// The largest BST in a binary tree is the largest subtree that is also a BST.

// Approach:
// 1. We will traverse the tree in postorder(bottom-up) fashion.
// 2. For each node, we will check these conditions:
//    a. The left subtree is a BST.
//    b. The right subtree is a BST.
//    c. The current node's value is greater than the maximum value in the left subtree and less than the minimum value in the right subtree.
// 3. If all conditions are satisfied, we can consider the current node as the root of a BST.
// 4. We will keep track of the maximum size of the BST found so far.


// We will track 4 values for each node:
// 1. The size of the BST.
// 2. The minimum value in the BST.
// 3. The maximum value in the BST.
// 4. A boolean value indicating whether the subtree is a BST or not.

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

// Structure to store the information of a subtree
class SubtreeInfo {
  public:
    int size;       // Size of the BST
    int min;        // Minimum value in the BST
    int max;        // Maximum value in the BST
    bool isBST;     // Whether the subtree is a BST or not
};

// Function to find the largest BST in a binary tree
SubtreeInfo largestBST(Node* root, int &maxSize) {
    // Base case: If the root is NULL, return size 0, min INT_MAX, max INT_MIN, and isBST true
    if (root == NULL) {
        return {0, INT_MAX, INT_MIN, true};
    }

    // Recursively find the largest BST in the left and right subtrees
    SubtreeInfo leftInfo = largestBST(root->left, maxSize);
    SubtreeInfo rightInfo = largestBST(root->right, maxSize);

    // Create a variable to store the current subtree's information
    SubtreeInfo currInfo;

    // Update the current subtree's size, min, max
    currInfo.size = leftInfo.size + rightInfo.size + 1; // Size of the current subtree, 1 is added for the current node
    currInfo.min = min(root->data, leftInfo.min);       // Minimum value in the current subtree, min is take because if lef subtree is empty then we will take root->data
    currInfo.max = max(root->data, rightInfo.max);      // Maximum value in the current subtree, max is take because if right subtree is empty then we will take root->data

    // Check if the current subtree is a BST
    if (leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min) {
        currInfo.isBST = true; // Current subtree is a BST
    } else {
        currInfo.isBST = false; // Current subtree is not a BST
    }

    // If the current subtree is a BST, update the maximum size found so far
    if (currInfo.isBST) {
        maxSize = max(maxSize, currInfo.size); // Update the maximum size of the BST found
    }

    return currInfo;
}

// Function to find the size of the largest BST in a binary tree
int largestBSTSize(Node* root) {
    int maxSize = 0; // Variable to store the maximum size of the BST found
    SubtreeInfo result = largestBST(root, maxSize); // Call the helper function to get the largest BST information
    return maxSize; // Return the maximum size of the BST found
}

// Function to create a sample binary tree
Node* createSampleBinayTree() {
  Node* root = new Node(10);
  root->left = new Node(5);
  root->right = new Node(15);
  root->left->left = new Node(1);
  root->left->right = new Node(8);
  root->right->right = new Node(7);
  return root;
}

int main() {
    Node* root = createSampleBinayTree();
    int size = largestBSTSize(root);
    cout << "Size of the largest BST in the binary tree: " << size << endl;
    return 0;
}

// Tree Structure:
//         10
//        /  \
//       5    15
//      / \     \
//     1   8    7
// The largest BST is the subtree rooted at node 5, which has size 3.

// Dry run:
// 1. Start at the root node (10).
// 2. Traverse to the left child (5).
// 3. Traverse to the left child (1).
// 4. Traverse to the left child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 5. Update maxSize to 0.
// 6. Traverse to the right child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 7. Update maxSize to 0.
// 8. Check if the subtree rooted at 1 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 9. Update currInfo: size = 1, min = 1, max = 1, isBST = true.
// 10. Update maxSize to 1.
// 11. Traverse to the right child (8).
// 12. Traverse to the left child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 13. Update maxSize to max(0, 1) = 1.
// 14. Traverse to the right child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 15. Update maxSize to max(0, 1) = 1.
// 16. Check if the subtree rooted at 8 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 17. Update currInfo: size = 1, min = 8, max = 8, isBST = true.
// 18. Update maxSize to max(1, 1) = 1.
// 19. Check if the subtree rooted at 5 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 20. Update currInfo: size = 3, min = 1, max = 8, isBST = true.
// 21. Update maxSize to max(1, 3) = 3.
// 22. Traverse to the right child (15).
// 23. Traverse to the left child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 24. Update maxSize to max(0, 3) = 3.
// 25. Traverse to the right child (7).
// 26. Traverse to the left child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 27. Update maxSize to max(0, 3) = 3.
// 28. Traverse to the right child (NULL), return size 0, min INT_MAX, max INT_MIN, and isBST true.
// 29. Update maxSize to max(0, 3) = 3.
// 30. Check if the subtree rooted at 7 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 31. Update currInfo: size = 1, min = 7, max = 7, isBST = true.
// 32. Update maxSize to max(0, 3) = 3.
// 33. Check if the subtree rooted at 15 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 34. Update currInfo: size = 2, min = 7, max = 15, isBST = false.
// 35. Check if the subtree rooted at 10 is a BST: leftInfo.isBST && rightInfo.isBST && root->data > leftInfo.max && root->data < rightInfo.min
// 36. Update currInfo: size = 6, min = 1, max = 15, isBST = false.
// 37. Return maxSize = 3.

