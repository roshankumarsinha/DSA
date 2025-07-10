// Write a function to find the height of binary tree.
// Height of a binary tree is the number of edges in the longest path from the root node to the leaf node.

// Approach 1 : Recursive Approach (DFS)
// Notes for Height of Binary Tree using DFS : https://takeuforward.org/data-structure/maximum-depth-of-a-binary-tree/
// 1. If the tree is empty (root is nullptr), return 0.
// 2. Recursively calculate the height of the left subtree.
// 3. Recursively calculate the height of the right subtree.
// 4. The height of the tree is 1 + max(left height, right height). We are adding 1 because root node is also included in the height.
// 5. Return the height of the tree.
// Time Complexity : O(N) where N is the number of nodes in the tree.
// Space Complexity : O(H) where H is the height of the tree.

// Approach 2 : Iterative Approach (BFS)
// 1. We can use Level Order Traversal to find the height of the tree.
// 2. We will traverse the tree level by level.
// 3. We will use a queue to store the nodes of the tree.
// 4. We will start with the root node and add it to the queue.
// 5. We will pop the front element of the queue and print it.
// 6. We will add the left and right children of the node to the queue.
// 7. We will repeat this process until the queue is empty.
// 8. We will keep a count of the levels and return the count.
// Time Complexity : O(N) where N is the number of nodes in the tree.
// Space Complexity : O(N) where N is the number of nodes in the tree.



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



// Approach 1 : Recursive Approach
// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \  / \
//    4   5 6  7
// Step-by-Step Execution
// We call height(root), and the function follows Depth-First Search (DFS).

// Step 1: Start at Root (1)
//  height(1)
//    Calls height(2) (left subtree)
//    Calls height(3) (right subtree)

// Step 2: Process Left Subtree (2)
//  height(2)
//    Calls height(4) (left child)
//    Calls height(5) (right child)
// Step 2.1: Process Left Child (4)
//  height(4)
//    height(nullptr) = 0 (left is null)
//    height(nullptr) = 0 (right is null)
//    return max(0, 0) + 1 = 1
// Step 2.2: Process Right Child (5)
//  height(5)
//    height(nullptr) = 0 (left is null)
//    height(nullptr) = 0 (right is null)
//    return max(0, 0) + 1 = 1
// Step 2.3: Calculate Height for 2
//  return max(1, 1) + 1 = 2

// Step 3: Process Right Subtree (3)
//  height(3)
//    Calls height(6) (left child)
//    Calls height(7) (right child)
// Step 3.1: Process Left Child (6)
//  height(6)
//    height(nullptr) = 0
//    height(nullptr) = 0
//    return max(0, 0) + 1 = 1
// Step 3.2: Process Right Child (7)
//  height(7)
//    height(nullptr) = 0
//    height(nullptr) = 0
//    return max(0, 0) + 1 = 1
// Step 3.3: Calculate Height for 3
//  return max(1, 1) + 1 = 2

// Step 4: Calculate Height for 1
//  return max(2, 2) + 1 = 3
//    Final Output
//    The height of the tree is 3.
int heightOfTree(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = heightOfTree(root->left);
    int rightHeight = heightOfTree(root->right);

    return 1 + max(leftHeight, rightHeight);
}


// Approach 2 : Iterative Approach
int heightOfTreeIterative(Node* root) {
    if (root == NULL) {
        return 0;
    }

    queue<Node*> q;
    q.push(root);
    int height = 0;

    while (!q.empty()) {
      int levelSize = q.size();  // Number of nodes at the current level
      height++; // Increase height for each level
      for (int i = 0; i < levelSize; i++) {
        Node* current = q.front();
        q.pop();

        if (current->left) {
          q.push(current->left);
        }
        if (current->right) {
          q.push(current->right);
        }
      }
    }

    return height;
}


// Function to create a sample tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    return root;
}

int main() {
    // Creating a sample tree
    Node* root = createSampleTree();

    // Height of the tree
    cout << "Height of the tree : " << heightOfTree(root) << endl;
    cout << "Height of the tree (Iterative) : " << heightOfTreeIterative(root) << endl;

    return 0;

}