// Write a function to convert normal BST to balanced BST.

// A height-balanced BST is defined as one in which the depths of the two subtrees of every node never differ by more than 1.

// Approach :
// 1. Inorder Traversal
//    a.  Do an inorder traversal of the BST to get a sorted array of values.
// 2. Build Balanced BST
//    a.  Use the sorted array to build a balanced BST using the middle element as root recursively.

// Intiution:
// 1. The inorder traversal of a BST gives us the elements in sorted order.
// 2. By using the middle element of the sorted array as the root, we ensure that the tree is balanced, as it divides the array into two halves.
// 3. The left half will be smaller than the root so that will be the left subtree, and the right half will be greater than the root so that will be the right subtree, which is the essence of a balanced BST.
// 4. Recursively applying this process to the left and right halves of the array will create a balanced BST.

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

// Function to build a balanced BST from a sorted array
Node* buildBalancedBST(vector<int>& elements, int start, int end) {
    if (start > end) {
        return NULL;
    }

    // Find the middle element
    int mid = start + (end - start) / 2;
    Node* root = new Node(elements[mid]);

    // Recursively build the left and right subtrees
    root->left = buildBalancedBST(elements, start, mid - 1);
    root->right = buildBalancedBST(elements, mid + 1, end);

    return root;
}

// Function to convert a normal BST to a balanced BST
Node* convertToBalancedBST(Node* root) {
    vector<int> elements;
    inorderTraversal(root, elements); // Perform inorder traversal to get sorted elements

    // Build a balanced BST from the sorted array
    return buildBalancedBST(elements, 0, elements.size() - 1);
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(1);
  root->right = new Node(2);
  root->right->right = new Node(3);
  root->right->right->right = new Node(4);
  root->right->right->right->right = new Node(5);
  return root;
}

int main() {
    Node* root = createSampleBST();
    cout << "Original BST (Inorder Traversal): ";
    vector<int> elements;
    inorderTraversal(root, elements);
    for (int val : elements) {
        cout << val << " ";
    }
    cout << endl;

    Node* balancedRoot = convertToBalancedBST(root);
    cout << "Balanced BST (Inorder Traversal): ";
    elements.clear();
    inorderTraversal(balancedRoot, elements);
    for (int val : elements) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

// Tree Structure :
//         1
//          \
//           2
//            \
//             3
//              \
//               4
//                \
//                 5

// Balanced BST Structure :
//         3
//        / \
//       2   4
//      /     \
//     1       5

