// Write a function to delete a node in a Binary Search Tree (BST).

// Approach:
// 1. Node has no children (Leaf Node)
//  a.  Simply remove the node.
// 2. Node has one child
//  a.  Replace the node with its only child.
// 3.Node has two children
//  a.  Find the inorder successor (smallest node in the right subtree) or find the inorder predecessor (largest node in the left subtree).
//  b.  Copy the inorder successor’s value to the node.
//  c.  Recursively delete the inorder successor.

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

// Function to delete a node in a BST
Node* deleteNodeInBST(Node* root, int key) {
    // If the root is NULL, return NULL
    if (root == NULL) {
        return root;
    }

    // If we found the key which needs to be deleted
    if (root->data == key) {
      // Case 1: Node has no children (Leaf Node)
      if (root->left == NULL && root->right == NULL) {
          delete root;
          return NULL;
      }

      // Case 2: Node has one child
      else if (root->left == NULL && root->right != NULL) { // If the node has only right child
          Node* temp = root->right;
          delete root;
          return temp;
      }
      else if (root->right == NULL && root->left != NULL) { // If the node has only left child
          Node* temp = root->left;
          delete root;
          return temp;
      }

      // Case 3: Node has two children
      else {
          Node* inorderSuccessor = root->right;
          // Find the inorder successor (smallest node in the right subtree)
          while (inorderSuccessor->left != NULL) {
              inorderSuccessor = inorderSuccessor->left;
          }
          // Copy the inorder successor’s value to the node
          root->data = inorderSuccessor->data;
          // Recursively delete the inorder successor
          root->right = deleteNodeInBST(root->right, inorderSuccessor->data);
      }

    }
    // If the key is greater than the root data, delete the key in the right subtree
    else if (key > root->data) {
        root->right = deleteNodeInBST(root->right, key);
    }
    // If the key is less than the root data, delete the key in the left subtree
    else {
        root->left = deleteNodeInBST(root->left, key);
    }

    return root;
}

// Level order traversal in level wise
void levelOrderTraversalLevelWise(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()){
        Node* frontNode = q.front();
        q.pop();
        
        if(frontNode == NULL){
            cout<<endl;
            if(!q.empty()){ 
                q.push(NULL);
            }
        }
        else{
            cout<< frontNode->data << " ";

            if(frontNode->left != NULL){
                q.push(frontNode->left);
            }
            if(frontNode->right != NULL){
                q.push(frontNode->right);
            }
        }
    }
}

// Function to create a sample BST
Node* createSampleBST() {
  Node* root = new Node(50);
  root->left = new Node(30);
  root->right = new Node(70);
  root->left->left = new Node(20);
  root->left->left->left = new Node(10);
  root->left->right = new Node(40);
  root->right->right = new Node(80);
  return root;
}

int main() {
    Node* root = createSampleBST();

    cout << "Level Wise Order before Deletion: " << endl;
    levelOrderTraversalLevelWise(root);

    int key = 30;
    root = deleteNodeInBST(root, key);
    cout << "Level Wise Order after Deletion of " << key << ": " << endl;
    levelOrderTraversalLevelWise(root);

    return 0;
}