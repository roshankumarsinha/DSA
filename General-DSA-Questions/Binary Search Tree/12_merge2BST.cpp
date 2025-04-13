// Write a function to merge 2 BSTs into a single BST.

// Merging two Binary Search Trees (BSTs) means creating a single balanced BST that contains all elements from both trees in sorted order.

// Approach 1:
// 1. Create a vector to store the elements of both BSTs, create inorder vector of both BSTs.
// 2. Merge the 2 sorted arrays into a single sorted array.
// 3. Create a balanced BST from the merged sorted array.
// 4. Return the root of the new balanced BST.
// 5. Time Complexity: O(N + M) for merging the two sorted arrays, where N and M are the number of nodes in the two BSTs.
// 6. Space Complexity: O(N + M) for storing the merged sorted array.

// Approach 2:
// 1. Convert both BSTs to sorted doubly linked lists.
//  a. The left pointer of each node will point to the previous node in the sorted order.
//  b. The right pointer of each node will point to the next node in the sorted order.
//  c. Use Inorder Traversal because it gives us the sorted order of elements in a BST.
//  d. Keep storing previous node in a variable at each step so that we can link the nodes.
//  e. The first node becomes the head of the doubly linked list.
// 2. Merge the two sorted doubly linked lists into a single sorted doubly linked list.
// 3. Convert the merged sorted doubly linked list to a balanced BST.
//  a. Use middle element of the linked list as the root of the BST and recursively do the same for left and right halves.
//  b. Ensures balanced BST.
// 4. Return the root of the new balanced BST.
// 5. Time Complexity: O(N + M).
// 6. Space Complexity: O(h1 + h2) for the recursion stack, where h1 and h2 are the heights of the two BSTs.

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

// Approach 1:
// Function to perform inorder traversal and store elements in a vector
void inorderTraversal(Node* root, vector<int>& elements) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, elements);
    elements.push_back(root->data);
    inorderTraversal(root->right, elements);
}

// Function to merge two sorted arrays into a single sorted array
vector<int> mergeArrays(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])
            result.push_back(a[i++]);
        else
            result.push_back(b[j++]);
    }
    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

// Function to create a balanced BST from a sorted array
Node* buildBalancedBST(const vector<int>& elements, int start, int end) {
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

// Function to merge two BSTs into a single balanced BST
Node* mergeBSTsApproach1(Node* root1, Node* root2) {
    vector<int> elements1, elements2;
    inorderTraversal(root1, elements1); // Perform inorder traversal to get sorted elements of the first BST
    inorderTraversal(root2, elements2); // Perform inorder traversal to get sorted elements of the second BST

    // Merge the two sorted arrays
    vector<int> mergedElements = mergeArrays(elements1, elements2);

    // Create a balanced BST from the merged sorted array
    return buildBalancedBST(mergedElements, 0, mergedElements.size() - 1);
}

// Approach 2:
// Function to convert a BST to a sorted doubly linked list
void bstToDoublyLinkedList(Node* root, Node*& head, Node*& prev) {
    if (root == NULL) {
        return;
    }

    // Convert the left subtree
    bstToDoublyLinkedList(root->left, head, prev);

    // Link the current node with the previous node
    if (prev == NULL) {
        head = root; // The first node becomes the head of the doubly linked list
    } else {
        prev->right = root; // Link the previous node to the current node
        root->left = prev;  // Link the current node to the previous node
    }
    prev = root; // Update the previous node to the current node

    // Convert the right subtree
    bstToDoublyLinkedList(root->right, head, prev);
}

// Function to merge two sorted doubly linked lists into a single sorted doubly linked list
Node* mergeDoublyLinkedLists(Node* head1, Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node* mergedHead = NULL;
    Node* mergedTail = NULL;

    // Merge the two sorted doubly linked lists
    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (mergedHead == NULL) {
                mergedHead = head1;
                mergedTail = head1;
            } else {
                mergedTail->right = head1;
                head1->left = mergedTail;
                mergedTail = head1;
            }
            head1 = head1->right;
        } else {
            if (mergedHead == NULL) {
                mergedHead = head2;
                mergedTail = head2;
            } else {
                mergedTail->right = head2;
                head2->left = mergedTail;
                mergedTail = head2;
            }
            head2 = head2->right;
        }
    }

    // Append any remaining nodes from either list
    while (head1 != NULL) {
        mergedTail->right = head1;
        head1->left = mergedTail;
        mergedTail = head1;
        head1 = head1->right;
    }
    while (head2 != NULL) {
        mergedTail->right = head2;
        head2->left = mergedTail;
        mergedTail = head2;
        head2 = head2->right;
    }

    return mergedHead; // Return the head of the merged doubly linked list
}

// Function to convert a sorted doubly linked list to a balanced BST
Node* sortedDoublyLinkedListToBST(Node*& head, int n) {
    if (n <= 0 || head == NULL) {
        return NULL;
    }

    // Recursively build the left subtree
    Node* left = sortedDoublyLinkedListToBST(head, n / 2);

    // Create a new node with the current head
    Node* root = head;
    root->left = left;

    // Move the head pointer to the next node
    head = head->right;

    // Recursively build the right subtree
    root->right = sortedDoublyLinkedListToBST(head, n - n / 2 - 1);

    return root;
}

// Function to merge two BSTs into a single balanced BST using doubly linked list approach
Node* mergeBSTsApproach2(Node* root1, Node* root2) {
    Node* head1 = NULL;
    Node* prev1 = NULL;
    bstToDoublyLinkedList(root1, head1, prev1); // Convert the first BST to a sorted doubly linked list

    Node* head2 = NULL;
    Node* prev2 = NULL;
    bstToDoublyLinkedList(root2, head2, prev2); // Convert the second BST to a sorted doubly linked list

    // Merge the two sorted doubly linked lists
    Node* mergedHead = mergeDoublyLinkedLists(head1, head2);

    // Count the number of nodes in the merged doubly linked list
    int n = 0;
    Node* temp = mergedHead;
    while (temp != NULL) {
        n++;
        temp = temp->right;
    }

    // Convert the merged sorted doubly linked list to a balanced BST
    return sortedDoublyLinkedListToBST(mergedHead, n);
}

// Function to create a sample BST1
Node* createSampleBST1() {
  Node* root = new Node(2);
  root->left = new Node(1);
  root->right = new Node(4);
  return root;
}

// Function to create a sample BST2
Node* createSampleBST2() {
  Node* root = new Node(6);
  root->left = new Node(5);
  root->right = new Node(7);
  return root;
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

int main() {
    Node* root1 = createSampleBST1(); // Create a sample BST1
    Node* root2 = createSampleBST2(); // Create a sample BST2

    // Merge the two BSTs using Approach 1
    Node* mergedRoot1 = mergeBSTsApproach1(root1, root2);
    cout << "Merged BST (Approach 1): ";
    inorderTraversal(mergedRoot1);
    cout << endl;

    // Merge the two BSTs using Approach 2
    Node* mergedRoot2 = mergeBSTsApproach2(root1, root2);
    cout << "Merged BST (Approach 2): ";
    inorderTraversal(mergedRoot2);
    cout << endl;

    return 0;
}

// Tree Structure of BST1:
//         2
//        / \
//       1   4
// Tree Structure of BST2:
//         6
//        / \
//       5   7

// Tree Structure of Merged BST:
//         5
//        / \
//       2   6
//      / \   \
//     1   4   7

// Step by Step Explanation and Dry Run using Approach 2:
// 1. Convert BST1 to a sorted doubly linked list:
//    - Inorder Traversal: 1 -> 2 -> 4
//    - Doubly Linked List: 1 <-> 2 <-> 4
// 2. Convert BST2 to a sorted doubly linked list:
//    - Inorder Traversal: 5 -> 6 -> 7
//    - Doubly Linked List: 5 <-> 6 <-> 7
// 3. Merge the two sorted doubly linked lists:
//    - Merged Doubly Linked List: 1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 7
// 4. Convert the merged sorted doubly linked list to a balanced BST:
//    - Middle element is 5, which becomes the root of the new BST.
//    - Left half: 1 <-> 2 <-> 4 becomes the left subtree
//    - Right half: 6 <-> 7 becomes the right subtree