// Write a function to create a Binary Search Tree (BST).

// Approach for inserting a node into a BST:
// 1. If the root is NULL, create a new node with the given data and return it.
// 2. If the data is greater than the root data, insert the data into the right subtree.
// 3. If the data is less than the root data, insert the data into the left subtree.
// 4. Return the root.

// Time Complexity: O(log N) in the average case and O(N) in the worst case.
// Space Complexity: O(log N) in the average case and O(N) in the worst case.

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

// CREATE BINARY SEARCH TREE
Node* inserIntoBST(Node* root, int data)  {
    // Create first node when root is null
    if  (root == NULL)  {
        Node* root = new Node(data);
        return root;
    }

    // Not for first Node, Adding data to right
    if  (data > root->data) {
        // Right Sub Tree
        root->right = inserIntoBST(root->right, data);
    }
    else  {   // Adding data to left
        // Left Sub Tree
        root->left = inserIntoBST(root->left, data);
    }

    return root;
}

void createBST(Node* &root){
    cout<< "Enter Data: " << endl;
    int data;
    cin >> data;

    // -1 is the terminating condition for the input, so if enter -1 we are stopping insertion
    while (data != -1)
    {
        root = inserIntoBST(root, data);
        cin >> data;
    }
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

int main(){
    Node* root = NULL;
    createBST(root);

    cout << "Level Wise Order: " << endl;
    levelOrderTraversalLevelWise(root);

    return 0;
}

/*
Binary Tree Input: 50 30 40 20 60 55 70 80 25 -1

OUTPUT:
Level Wise Order: 
50 
30 60 
20 40 55 70 
25 80 
*/


// Search value in BST
// https://takeuforward.org/data-structure/search-in-a-binary-search-tree-2/ -> Follow this link for searching in a BST

// Approach for searching in a BST:
// 1. If the root is NULL, return NULL.
// 2. If the data is equal to the root data, return the root.
// 3. If the data is greater than the root data, search in the right subtree.
// 4. If the data is less than the root data, search in the left subtree.

// Time Complexity: O(log N) in the average case and O(N) in the worst case.
// Space Complexity: O(log N) in the average case and O(N) in the worst case.

// Function to search for a value in a BST
// Node* searchInBST(Node* root, int data) {
//     // If the root is NULL or the data is found, return the root
//     if (root == NULL || root->data == data) {
//         return root;
//     }

//     // If the data is greater than the root data, search in the right subtree
//     if (data > root->data) {
//         return searchInBST(root->right, data);
//     }

//     // If the data is less than the root data, search in the left subtree
//     return searchInBST(root->left, data);
// }

// But note that recursion requires extra space in the form of a function call stack. We can also solve this problem iteratively using a while loop. Iterative solutions are more efficient in terms of space complexity.

// Iterative approach to search for a value in a BST
// Node* searchInBST(Node* root, int data) {
//     // Traverse the tree until the root is NULL
//     while (root != NULL) {
//         // If the data is found, return the root
//         if (root->data == data) {
//             return root;
//         }

//         // If the data is greater than the root data, search in the right subtree
//         if (data > root->data) {
//             root = root->right;
//         } else {
//             // If the data is less than the root data, search in the left subtree
//             root = root->left;
//         }
//     }

//     // If the data is not found, return NULL
//     return NULL;
// }