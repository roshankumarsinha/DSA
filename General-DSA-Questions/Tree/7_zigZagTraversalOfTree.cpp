// Write a function to perform zigzag traversal of a binary tree.
// Zig-Zag traversal of a binary tree means:

// Level 1 → Left to Right
// Level 2 → Right to Left
// Level 3 → Left to Right
// Level 4 → Right to Left
// … and so on.

// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \  / \
//    4   5 6  7
// Zig-Zag Traversal : 1 3 2 4 5 6 7

// Approach : Level Order Traversal using Queue
// 1. We will use a queue to store the nodes of the tree.
// 2. We will start with the root node and add it to the queue.
// 3. We will use a flag to keep track of the level.
// 4. If the flag is even, we will print the nodes from left to right.
// 5. If the flag is odd, we will print the nodes from right to left.
// 6. We will repeat this process until the queue is empty.
// 7. The time complexity for this approach is O(N) where N is the number of nodes in the tree.
// 8. The space complexity for this approach is O(N) where N is the number of nodes in the tree.

#include <iostream>
#include <queue>
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

// Function to perform zigzag traversal of a binary tree
vector<int> zigzagTraversal(Node* root) {
  vector<int> result;   // Vector to store the nodes of the tree
  if (root == NULL) {
    return result;
  }

  queue<Node*> q;   // Queue to store the nodes of the tree
  q.push(root);

  bool leftToRight = true;   // Flag to keep track of the level, if true, print nodes from left to right and if false, print nodes from right to left

  while (!q.empty()) {
    int levelSize = q.size();   // Number of nodes at the current level
    deque<int> levelNodes;   // Vector to store the nodes of the current level

    for (int i = 0; i < levelSize; i++) {
      Node* current = q.front();
      q.pop();

      if (leftToRight) {
        levelNodes.push_back(current->data);   // Add the nodes to the deque from left to right
      } else {
        levelNodes.push_front(current->data);   // Add the nodes to the deque from right to left
      }

      if (current->left) {
        q.push(current->left);
      }
      if (current->right) {
        q.push(current->right);
      }
    }

    for (int i = 0; i < levelNodes.size(); i++) {
      result.push_back(levelNodes[i]);   // Add the nodes of the current level to the result vector
    }

    leftToRight = !leftToRight;   // Toggle the flag for the next level
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

int main () {
  Node* root = createSampleTree();
  vector<int> result = zigzagTraversal(root);

  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}