// Create a Binary Tree
// Creation of binary tree notes : https://takeuforward.org/binary-tree/binary-tree-representation-in-c/

#include <iostream>
#include <queue>
using namespace std;

class node {
  public:
    int data;
    node* left;
    node* right;

    node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

node* buildTree(node* root) {
    int data;
    cout << "Enter Root data : "<<endl;
    cin >> data;

    // If data is -1, it means there is no node, so return NULL
    if(data == -1) {
        return NULL;
    }

    root = new node(data);
    cout << "Enter left child of " << data << " : ";
    root->left = buildTree(root->left);
    cout << "Enter right child of " << data << " : ";
    root->right = buildTree(root->right);

    return root;

    // Recursion will go like this :
    // 1. Read data = 1
    //    Create node with value 1
    //    node* root = new node(1);
    // 2. Read data = 3
    //    Create left child of 1
    //    root->left = buildTree(); // Recursive call becomes buildTree(3)
    // 3. Read data = 7
    //    Create left child of 3
    //    root->left->left = buildTree(); // Recursive call becomes buildTree(7)
    // 4. Read data = -1
    //    Left child of 7 is NULL
    //    root->left->left->left = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 5. Read data = -1
    //    Right child of 7 is NULL
    //    root->left->left->right = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 6. Read data = 11
    //    Create right child of 3
    //    root->left->right = buildTree(); // Recursive call becomes buildTree(11)
    // 7. Read data = -1
    //    Left child of 11 is NULL
    //    root->left->right->left = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 8. Read data = -1
    //    Right child of 11 is NULL
    //    root->left->right->right = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 9. Read data = 5
    //    Create right child of 1
    //    root->right = buildTree(); // Recursive call becomes buildTree(5)
    // 10. Read data = 17
    //    Create left child of 5
    //    root->right->left = buildTree(); // Recursive call becomes buildTree(17)
    // 11. Read data = -1
    //    Left child of 17 is NULL
    //    root->right->left->left = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 12. Read data = -1
    //    Right child of 17 is NULL
    //    root->right->left->right = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 13. Read data = -1
    //    Right child of 5 is NULL
    //    root->right->right = buildTree(); // Recursive call becomes buildTree(-1) -> returns NULL
    // 14. Returns root

}

// Build a Binary Tree using Level Order Traversal
// Example :
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
// Level Order Traversal : 1 3 5 7 11 17
// Output will look like :
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
node* buildTreeFromLevelOrder(node* root) {
    int data;
    cout << "Enter Root data : "<<endl;
    cin >> data;

    // If data is -1, it means there is no node, so return NULL
    if(data == -1) {
        return NULL;
    }
    root = new node(data);
    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
      node* current = q.front();
      q.pop();

      cout << "Enter left node for : " << current->data << endl;
      int leftData;
      cin >> leftData;

      if (leftData != -1) {
        current -> left = new node(leftData);
        q.push(current -> left);
      }

      cout << "Enter right node for : " << current->data << endl;
      int rightNode;
      cin >> rightNode;

      if (rightNode != -1) {
        current -> right = new node(rightNode);
        q.push(current -> right);
      }
    }

    return root;

}


// Binary Tree Traversals Notes : https://takeuforward.org/binary-tree/binary-tree-traversal-inorder-preorder-postorder/

// Level Order Traversal is also known as Breadth First Search (BFS)
// In this traversal, we traverse the tree level by level
// We use a queue to store the nodes of the tree
// We start with the root node and add it to the queue
// Then we pop the front element of the queue and print it
// Then we add the left and right children of the node to the queue
// We repeat this process until the queue is empty
// Time Complexity : O(N) where N is the number of nodes in the tree
// Space Complexity : O(N) where N is the number of nodes in the tree
// Level Order Traversal Notes : https://takeuforward.org/data-structure/level-order-traversal-of-a-binary-tree/
void levelOrderTraversal(node* root) {
    if(root == NULL) {
        return;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
      node* temp = q.front();
      q.pop();

      cout << temp->data << " ";
      if (temp->left) q.push(temp->left);
      if (temp->right) q.push(temp->right);
    }

    // If we want to add Enter as well after each level, we can add a NULL node after each level
    // and check if the node is NULL, then add Enter
    // Code will look like :
    // if (root == NULL) return;
    // queue<node*> q;
    // q.push(root);
    // q.push(NULL);
    // while (!q.empty()) {
    //   node* temp = q.front();
    //   q.pop();
    //   if (temp == NULL) {
    //     purana level complete traverse ho chuka hai
    //     cout << endl;
    //     if (!q.empty()) {
    //       q.push(NULL);  // Next level ke liye NULL add karo
    //     }
    //   }
    //   else {
    //     cout << temp->data << " ";
    //     if (temp->left) q.push(temp->left);
    //     if (temp->right) q.push(temp->right);
    //   }
    // }
}

// InOrder Traversal : LNR (Left Node Right)
// Example :
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
// InOrder Traversal : 7 3 11 1 17 5
// InOrder Traversal Notes : https://takeuforward.org/data-structure/inorder-traversal-of-binary-tree/
void inOrderTraversal(node* root) {
  // Base Case
  if(root == NULL) {
      return;
  }

  inOrderTraversal(root->left); // L
  cout << root->data << " ";  // N
  inOrderTraversal(root->right);  // R
}

// PreOrder Traversal : NLR (Node Left Right)
// Example :
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
// PreOrder Traversal : 1 3 7 11 5 17
// PreOrder Traversal Notes : https://takeuforward.org/data-structure/preorder-traversal-of-binary-tree/
void preOrderTraversal(node* root) {
  // Base Case
    if(root == NULL) {
        return;
    }

  cout << root->data << " ";  // N
  preOrderTraversal(root->left);  // L
  preOrderTraversal(root->right); // R
}

// PostOrder Traversal : LRN (Left Right Node)
// Example :
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
// PostOrder Traversal : 7 11 3 17 5 1
// PostOrder Traversal Notes : https://takeuforward.org/data-structure/post-order-traversal-of-binary-tree/
void postOrderTraversal(node* root) {
  // Base Case
    if(root == NULL) {
        return;
    }

  postOrderTraversal(root->left);  // L
  postOrderTraversal(root->right); // R
  cout << root->data << " ";  // N
}

// Count the number of leaf nodes in a binary tree
// Approach : Traverse the tree in InOrder or PreOrder or PostOrder fashion and keep a count of leaf nodes
// If a node is a leaf node, increment the count
void inOrder(node* root, int &count) {
  if (root == NULL) {
    return;
  }
  inOrder(root->left, count);
  if (root->left == NULL && root->right == NULL) {
    count++;
  }
  inOrder(root->right, count);
}

int countLeafNodes(node* root) {
    int count = 0;
    inOrder(root, count);
    return count;
}

int main() {
    node* root = NULL;
    // Create a binary tree for : 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    // Output will look like :
    //          1
    //         / \
    //        3   5
    //       / \  /
    //      7  11 17
    root = buildTree(root);
    // root = buildTreeFromLevelOrder(root);
    cout << "Binary Tree Created Successfully!" << endl << endl;
    cout << "Tree Traversals : " << endl;
    cout << "Level Order Traversal : ";
    levelOrderTraversal(root);
    cout << endl;
    cout << "InOrder Traversal : ";
    inOrderTraversal(root);
    cout << endl;
    cout << "PreOrder Traversal : ";
    preOrderTraversal(root);
    cout << endl;
    cout << "PostOrder Traversal : ";
    postOrderTraversal(root);
    cout << endl;
    cout << "Number of Leaf Nodes : " << countLeafNodes(root) << endl;
    return 0;
}
