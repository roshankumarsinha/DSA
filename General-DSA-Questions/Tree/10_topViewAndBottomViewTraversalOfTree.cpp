// Write a function to perform top view traversal of a binary tree.
// The Top View of a binary tree consists of the first visible nodes from the top when looking at the tree from a vertical perspective.

// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6

// Top View : 4 2 1 3 6

// Approach : Level Order Traversal using Queue
// 1. It is same as vertical traversal but we need to print only the first node at each horizontal distance.
// 2. We will use a map to store the nodes at each horizontal distance.
// 3. We will create a map something like this : map<int, int> nodes; where the first int represents the horizontal distance and the second int represents the node at that horizontal distance.
// 4. We will start with the root node and add it to the queue.
// 5. We will keep track of the horizontal distance of each node.
// 6. We will only add the node to the map if it is the first node at that horizontal distance.
// 6. We will repeat this process until the queue is empty.
// 7. The time complexity for this approach is O(N Log N) where N is the number of nodes in the tree. It is 0(N Log N) because we are using a map to store the nodes at each horizontal distance and this map automatically sorts the nodes based on the horizontal distance.
// 8. The space complexity for this approach is O(N) where N is the number of nodes in the tree.

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

// Function to do top-view Traversal
vector<int> topView(Node* root) {
  vector<int> result;   // Vector to store the nodes of the tree
  if (root == NULL) {
    return result;
  }

  map<int, int> nodes;   // Map to store the nodes at each horizontal distance, where the first int represents the horizontal distance and the second int represents the node at that horizontal distance

  queue<pair<Node*, int>> q;   // Queue to store the nodes of the tree along with their horizontal distance
  q.push({root, 0});   // Push the root node along with the horizontal distance 0

  while (!q.empty()) {
    Node* current = q.front().first;  // Get the current node
    int hd = q.front().second;  // Get the horizontal distance of the current node
    q.pop();

    if (nodes.find(hd) == nodes.end()) {   // If the horizontal distance is not present in the map, add the node to the map. We can also write as if (nodes.count(hd) == 0)
      nodes[hd] = current->data;  // Add the node to the map
    }

    if (current->left) {
      q.push({current->left, hd - 1});   // Push the left child along with the horizontal distance
    }

    if (current->right) {
      q.push({current->right, hd + 1});   // Push the right child along with the horizontal distance
    }
  }

  for (auto it : nodes) {
    result.push_back(it.second);   // Add the nodes to the result vector
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
  vector<int> result = topView(root);
  cout << "Top View Traversal : ";
  for (int val : result) {
    cout << val << " ";
  }
  cout << endl;
  return 0;
}


// Bottom View Traversal
// The Bottom View of a binary tree consists of the last visible nodes from the bottom when looking at the tree from a vertical perspective.
// Example : Tree considered here is :
//        1
//       / \
//      2   3
//     / \   \
//    4   5   6
// Output : 4 2 5 3 6

// Approach :
// Approach is same as top view, we just need to overwrite the value of the node at each horizontal distance which comes later in the traversal.

// Instead of :
// if (nodes.find(hd) == nodes.end()) {   // If the horizontal distance is not present in the map, add the node to the map. We can also write as if (nodes.count(hd) == 0)
//   nodes[hd] = current->data;  // Add the node to the map
// }
// We will write :
// nodes[hd] = current->data;  // Overwrite the value of the node at that horizontal distance, we remove the if condition, so that the value of the node at that horizontal distance is overwritten by the latest node.

// Rest all code will remain same
