// Write a function to find minimum time to burn a binary tree from target node.
// Given a binary tree and a target node, find the minimum time required to burn the entire tree if the fire starts at the target node.
// The fire spreads to adjacent nodes (parent and children) in 1 second per step.

// Example:
//      1
//    /   \
//   2     3
//  / \     \
// 4   5     6
//    /
//   7
// Fire starts at 5.
// Burning Process:
// 1. t = 0 → Fire starts at 5
// 2. t = 1 → 5 spreads fire to 2 and 7
// 3. t = 2 → 2 spreads fire to 1, 4, and 7 spreads fire to NULL
// 4. t = 3 → 1 spreads fire to 3 and 4 spreads fire to NULL
// 5. t = 4 → 3 spreads fire to 6
// 🔥 Total time = 4 seconds

// Approach:
// We can solve this problem in 3 steps:
// 1. Create a map to store the parent of each node. Find parent of each node (so we can traverse left, right and up).
// 2. Find the target node in tree.
// 3. Perform a level order traversal starting from the target node to find the time taken to burn the entire tree.

// Step 1: Build Parent Mapping
//    a.  Perform a BFS traversal to store each node’s parent in a hash map (unordered_map<Node*, Node*>). This can give parent in O(1) time.
//    b.  We can combine the Step 2 as well and find the target node in the same traversal.

// Step 3: Level Order Traversal to find minimum time to burn the tree
//   a.  Start with the target node and add it to the queue.
//   b.  Keep track of the time taken to burn the tree.
//   c. Track visited node using a map. Something like map<Node*, bool> visited. We are keeping track of visited nodes to avoid visiting the same node again.
//   d.  While the queue is not empty, perform the following steps:
//       i.  Get the front element of the queue.
//       ii. If the left child is not visited, add it to the queue and mark it as visited.
//       iii. If the right child is not visited, add it to the queue and mark it as visited.
//       iv. If the parent(up) is not visited, add it to the queue and mark it as visited.
//       v.  Increment the time taken to burn the tree. If something is added to the queue, increment the time.
//   e.  Return the time taken to burn the tree.

#include <iostream>
#include <queue>
#include <unordered_map>
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

// Function to build parent mapping and find the target node
Node* buildParentMapping(Node* root, unordered_map<Node*, Node*> &parent, int target) {
    queue<Node*> q;
    q.push(root);
    Node* targetNode = NULL;  // To store the target node

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Find the target node and store it
        if (current->data == target) {
            targetNode = current;
        }

        // Store the parent of the left child
        if (current->left) {
            parent[current->left] = current;
            q.push(current->left);
        }

        // Store the parent of the right child
        if (current->right) {
            parent[current->right] = current;
            q.push(current->right);
        }
    }

    return targetNode;
}

// Function to find the minimum time to burn the tree
int burnTree(Node* root, unordered_map<Node*, Node*> &parent) {
    unordered_map<Node*, bool> visited;  // To store the visited nodes
    queue<Node*> q;  // Queue to store the nodes of the tree
    q.push(root);  // Push the root node
    visited[root] = true;  // Mark the root node as visited
    int time = 0;  // To store the time taken to burn the tree

    while(!q.empty()) {
      bool flag = false;  // To check if any node is added to the queue or not, if not added, then we don't need to increment the time
      int levelSize = q.size();  // Number of nodes at the current level, so we can process all nodes at the same time for the current time step
      for (int i = 0; i < levelSize; i++) {
        Node* current = q.front();  // Get the current node
        q.pop();

        // If the left child is not visited, add it to the queue and mark it as visited
        if (current->left && !visited[current->left]) {
          flag = true;
          q.push(current->left);
          visited[current->left] = true;
        }

        // If the right child is not visited, add it to the queue and mark it as visited
        if (current->right && !visited[current->right]) {
          flag = true;
          q.push(current->right);
          visited[current->right] = true;
        }

        // If the parent is not visited, add it to the queue and mark it as visited
        if (parent[current] && !visited[parent[current]]) {
          flag = true;
          q.push(parent[current]);
          visited[parent[current]] = true;
        }
      }

      // Increment the time taken to burn the tree, if any node is added to the queue
      if (flag) {
        time++;
      }
    }

    return time;
}

int minTime(Node* root, int target) {
    unordered_map<Node*, Node*> parent;  // To store the parent of each node
    Node* targetNode = buildParentMapping(root, parent, target);  // Build parent mapping and find the target node
    return burnTree(targetNode, parent);  // Find the minimum time to burn the tree
}

// Function to create a sample tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(7);
    root->right->right = new Node(6);
    return root;
}

int main() {
    Node* root = createSampleTree();
    int target = 5;
    cout << "Minimum time to burn the tree: " << minTime(root, target) << endl;
    return 0;
}

// Dry Run Example :-
// Consider the following tree:
//         1
//        / \
//       2   3
//      / \   \
//     4   5   6
//        /
//       7
// 🔥 Target Node: 5

// Step 1: Parent Mapping
// Parent Map:
// 2 -> 1, 3 -> 1, 4 -> 2, 5 -> 2, 7 -> 5, 6 -> 3

// Step 2: BFS Simulation
// Time	  Burning Nodes	  Spread Fire To
// 0	    5	                2, 7
// 1	    2, 7	            1, 4
// 2	    1, 4	            3
// 3	    3	                6
// 4	    6	              (No more nodes)
// 🔥 Total Time Taken = 4 seconds

// Time Complexity: O(N)
// Space Complexity: O(N)
