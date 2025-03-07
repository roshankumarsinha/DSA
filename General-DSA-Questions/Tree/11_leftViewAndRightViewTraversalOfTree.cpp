// Write a function to perform left view and right view traversal of a binary tree.
// The Left View of a binary tree consists of the first node visible from the left at each level.
// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6
// Left View Traversal : 1 2 4

// Approach :
// 1. Perform level-order traversal using a queue.
// 2. Track the first node of each level using a boolean flag.
// 3. Store the first node of every level.

// Similar to right view traversal, we can perform left view traversal of a binary tree.
// The only difference is that we will store the last node of each level instead of the first node.
// The time complexity for this approach is O(N) where N is the number of nodes in the tree.

#include <iostream>
#include <queue>
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

// Function to perform left view traversal of a binary tree
vector<int> leftView(Node* root) {
    vector<int> result;   // Vector to store the nodes of the tree
    if (root == NULL) {
        return result;
    }

    queue<Node*> q;   // Queue to store the nodes of the tree
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();   // Number of nodes at the current level
        bool firstNode = true;   // Flag to keep track of the first node at each level

        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();   // Get the current node
            q.pop();

            if (firstNode) {
                result.push_back(current->data);   // Store the first node of the level
                firstNode = false;
            }

            if (current->left) {
                q.push(current->left);   // Push the left child
            }

            if (current->right) {
                q.push(current->right);   // Push the right child
            }
        }
    }

    return result;
}

// Function to perform right view traversal of a binary tree
vector<int> rightView(Node* root) {
    vector<int> result;   // Vector to store the nodes of the tree
    if (root == NULL) {
        return result;
    }

    queue<Node*> q;   // Queue to store the nodes of the tree
    q.push(root);

    while (!q.empty()) {
      int levelSize = q.size();   // Number of nodes at the current level
      Node* lastNode = NULL;   // Pointer to store the last node of the level

      for (int i = 0; i < levelSize; i++) {
        Node* current = q.front();   // Get the current node
        q.pop();

        lastNode = current;   // Update the last node of the level, each time we are updating the last node

        if (current->left) {
          q.push(current->left);   // Push the left child
        }

        if (current->right) {
          q.push(current->right);   // Push the right child
        }
      }

      result.push_back(lastNode->data);   // Store the last node of the level, We are stroing the last node after completing the level
    }

    return result;
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
  vector<int> leftResult = leftView(root);
  vector<int> rightResult = rightView(root);

  cout << "Left View Traversal : ";
  for (int i = 0; i < leftResult.size(); i++) {
    cout << leftResult[i] << " ";
  }
  cout << endl;

  cout << "Right View Traversal : ";
  for (int i = 0; i < rightResult.size(); i++) {
    cout << rightResult[i] << " ";
  }
  cout << endl;

  return 0;
}
