// Write a function to flatten a BST into sorted Linked List.

// Flattening a BST to a sorted linked list means converting the tree into a right-skewed tree (like a linked list), where:
//  1.  All left pointers are nullptr.
//  2.  Nodes appear in inorder sequence.

// Approach : Inorder Traversal + Pointer Rewiring
// 1. Perform an inorder traversal of the BST and store the elements in a vector. The inorder traversal of a BST gives us a sorted array.
// 2. Create a new linked list from the sorted elements.
// 3. Link the nodes in the linked list such that each node's right pointer points to the next node in the sorted order.
// 4. Set the left pointers of all nodes to nullptr.
// 5. Return the head of the linked list.
// 6. Time Complexity: O(N) for the inorder traversal and O(N) for creating the linked list, resulting in O(N) overall.
// 7. Space Complexity: O(N) for storing the elements in the vector and O(N) for the linked list.


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

// Function to flatten a BST into a sorted linked list
Node* flattenBSTToSortedLL(Node* root) {
    vector<int> elements;
    inorderTraversal(root, elements); // Perform inorder traversal to get sorted elements

    // Create a new linked list from the sorted elements
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < elements.size(); i++) {
        Node* newNode = new Node(elements[i]);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->right = newNode; // Link the new node to the tail
            tail = newNode; // Move the tail pointer to the new node
        }
    }

    return head; // Return the head of the linked list
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(5);
  root->left = new Node(3);
  root->right = new Node(7);
  root->left->left = new Node(2);
  root->left->right = new Node(4);
  root->right->right = new Node(8);
  return root;
}

int main() {
    Node* root = createSampleBST();
    Node* head = flattenBSTToSortedLL(root);

    // Print the sorted linked list
    cout << "Flattened BST to Sorted Linked List: ";
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->right;
    }
    cout << endl;

    return 0;
}

// Tree Structure :
//         5
//        / \
//       3   7
//      / \   \
//     2   4   8
// Flattened BST to Sorted Linked List: 2 3 4 5 7 8