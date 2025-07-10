// Write a function to perform vertical traversal of a binary tree.
// Notes : https://takeuforward.org/data-structure/vertical-order-traversal-of-binary-tree/
// In vertical order traversal, we group the nodes column-wise from left to right. Nodes in the same column are ordered top to bottom.
//    Nodes at the same vertical level but different depths are arranged from top to bottom.
//    If two nodes have the same vertical level and depth, they are arranged from left to right.

// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6

// Vertical Order Output :
// 4
// 2
// 1 5
// 3
// 6
// [[4], [2], [1, 5], [3], [6]]

// Approach : Level Order Traversal using Queue
// 1. Think of the tree as a 2D plane where the x-axis represents the horizontal distance and the y-axis represents the depth.
// 2. The root node will have a horizontal distance of 0 and depth of 0. The left child of the root will have a horizontal distance of -1 and depth of 1. The right child of the root will have a horizontal distance of 1 and depth of 1.
// 3. We will use a map to store the nodes at each horizontal distance.
// 4. We will create a map something like this : map<int, map<int, vector<int>>> nodes; where the first int represents the horizontal distance, the second int represents the depth, and the vector<int> represents the nodes at that horizontal distance and depth. 
// 5. We will start with the root node and add it to the queue.
// 6. We will keep track of the horizontal distance and depth of each node.
// 7. We will repeat this process until the queue is empty.
// 8. The time complexity for this approach is O(N Log N) where N is the number of nodes in the tree. It is 0(N Log N) because we are using a map to store the nodes at each horizontal distance and depth.
// 9. The space complexity for this approach is O(N) where N is the number of nodes in the tree.

#include <iostream>
#include <queue>
#include <map>
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

// Function for vertical Traversal
vector<int> verticalTraversal(Node* root) {
  vector<int> result;   // Vector to store the nodes of the tree
  if (root == NULL) {
    return result;
  }

  map<int, map<int, vector<int>>> nodes;   // Map to store the nodes at each horizontal distance and depth

  queue<pair<Node*, pair<int, int>>> q;   // Queue to store the nodes of the tree along with their horizontal distance and depth
  q.push({root, {0, 0}});   // Push the root node along with its horizontal distance and depth, or we can write as q.push(make_pair(root, make_pair(0, 0)));

  while (!q.empty()) {
    Node* current = q.front().first;   // Get the current node
    int hd = q.front().second.first;   // Get the horizontal distance of the current node
    int depth = q.front().second.second;   // Get the depth or level of the current node
    q.pop();   // Pop the front element

    nodes[hd][depth].push_back(current->data);   // Store the current node in the map

    if (current->left) {
      q.push({current->left, {hd - 1, depth + 1}});   // Push the left child along with its horizontal distance and depth, as horizontal distance of left child will be -1 but depth will increase by 1
    }
    if (current->right) {
      q.push({current->right, {hd + 1, depth + 1}});   // Push the right child along with its horizontal distance and depth, as horizontal distance of right child will be +1 but depth will increase by 1
    }
  }

  for (auto it : nodes) {
    for (auto itr : it.second) {
      for (int val : itr.second) {
        result.push_back(val);   // Push the nodes to the result vector
      }
    }
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
  vector<int> result = verticalTraversal(root);

  cout << "Vertical Traversal : ";
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}