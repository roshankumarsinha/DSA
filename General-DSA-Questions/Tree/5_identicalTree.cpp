// Write a function to check if two binary trees are identical or not.
// Two binary trees are considered identical if they have the same structure and the same node values.

// Approach : Recursive Approach
// 1. If both trees are empty, return true.
// 2. If one of the trees is empty and the other is not, return false.
// 3. If the values of the nodes are not equal, return false.
// 4. Recursively check if the left subtree of the first tree is identical to the left subtree of the second tree.
// 5. Recursively check if the right subtree of the first tree is identical to the right subtree of the second tree.
// 6. If all the conditions are satisfied, return true.

// The time complexity for this approach is O(n) because we are traversing each node only once.
// The space complexity for this approach is O(n) because of the recursive stack space.

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

bool identicalTree(Node* root1, Node* root2) {
  if (root1 == NULL && root2 == NULL) {   // If both trees are empty, return true
    return true;
  }

  if (root1 == NULL || root2 == NULL) {   // If one of the trees is empty and the other is not, return false
    return false;
  }

  bool left = identicalTree(root1->left, root2->left);  // Recursively check if the left subtree of the first tree is identical to the left subtree of the second tree
  bool right = identicalTree(root1->right, root2->right);  // Recursively check if the right subtree of the first tree is identical to the right subtree of the second tree

  bool isIdenticalValue = root1->data == root2->data;  // If the values of the nodes are not equal, return false

  return left && right && isIdenticalValue;
}

// Function to create a sample tree
Node* createSampleTree1() {
  Node* root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  return root;
}

Node* createSampleTree2() {
  Node* root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  return root;
}

int main() {
  Node* root1 = createSampleTree1();
  Node* root2 = createSampleTree2();

  if (identicalTree(root1, root2)) {
    cout << "Trees are identical." << endl;
  } else {
    cout << "Trees are not identical." << endl;
  }
  return 0;
}
