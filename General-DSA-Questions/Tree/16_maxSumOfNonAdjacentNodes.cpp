// Write a function to find maximum sum of nodes in Binary tree such that no two nodes are adjacent to each other.
// It means that if we select root node, we cannot select direct children of root node and if we select any child of root node, we cannot select their direct children and root node.

// Example:
// Tree considered here is :
//        10
//       /  \
//      1    2
//     / \    \
//    20 30   25

// Options are:
// 1. If we choose root node 10, we cannot choose 1 and 2. So, maximum sum = 10 + 20 + 30 + 25 = 85
// 2. If we do not include root node 10, we can choose 1 and 2. So, maximum sum = 1 + 2 + 20 + 30 + 25 = 78
// So, maximum sum = 85

// Approach:
// 1. For each node, we maintain two values in a pair<int, int>:
//    a.  first: The maximum sum when the current node is included
//    b.  second: The maximum sum when the current node is excluded

// Key Observations :-
//  1.  If we include the current node, we must exclude its children.
//  2.  If we exclude the current node, we take the maximum sum of each child (whether it was included or not).
//  3.  We recursively calculate these values for the left and right subtrees and use them to determine the optimal sum at each node.

// Steps in the Algorithm :-
//  1.  Base Case:
//    a.  If root == NULL, return {0, 0} (no contribution to the sum).

//  2.  Recursive Calls:
//    a.  Compute the results for left and right subtrees using solve(root->left) and solve(root->right).

//  3.  Compute the Two Cases for the Current Node:
//    a.  Include the current node:
//      a1. Sum of the current node's value + exclude sum of left child + exclude sum of right child
//      a2. include = root->data + left.second + right.second
//    b.  Exclude the current node:
//      b1. Take the maximum sum from each child (whether included or not).
//      b2. exclude = max(left.first, left.second) + max(right.first, right.second)

//  4.  Return a Pair: {include, exclude}
//    a.  include → The sum if the current node is included.
//    b.  exclude → The sum if the current node is excluded.

//  5.  Final Result:
//    a.  The maximum of include and exclude at the root node.


// Dry Run of above example Tree:
// Step-by-Step Calculation :
//    Node   	Include (first)   	Exclude (second)
// 1. 20	    20 + 0 + 0 = 20	    max(0,0) + max(0,0) = 0
// 2. 30	    30 + 0 + 0 = 30	    max(0,0) + max(0,0) = 0
// 3. 25	    25 + 0 + 0 = 25	    max(0,0) + max(0,0) = 0
// 4. 1	      1 + 0 + 0 = 1	      max(20,0) + max(30,0) = 50
// 5. 2	      2 + 0 + 0 = 2	      max(0,0) + max(25,0) = 25
// 6. 10	    10 + 50 + 25 = 85	  max(1,50) + max(2,25) = 77

// So, maximum sum = 85




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

// Function to find the maximum sum of nodes in a binary tree such that no two nodes are adjacent to each other
pair<int, int> solve(Node* root) {    // Here, first int represents the maximum sum of nodes when the current node is included and second int represents the maximum sum of nodes when the current node is excluded
    // Base Case
    if (root == NULL) {
        return {0, 0};
    }

    pair<int, int> left = solve(root->left);  // Recursively find the maximum sum of nodes for the left subtree
    pair<int, int> right = solve(root->right);  // Recursively find the maximum sum of nodes for the right subtree

    int include = root->data + left.second + right.second;  // If the current node is included, then sum of the current node, left child's excluded sum and right child's excluded sum
    int exclude = max(left.first, left.second) + max(right.first, right.second);  // If the current node is excluded, then maximum of left child's included and excluded sum and maximum of right child's included and excluded sum

    return {include, exclude};
}

int maxSumOfNonAdjacentNodes(Node* root) {
    pair<int, int> result = solve(root);
    return max(result.first, result.second);
}

Node* createSampleTree() {
    Node* root = new Node(10);
    root->left = new Node(1);
    root->right = new Node(2);
    root->left->left = new Node(20);
    root->left->right = new Node(30);
    root->right->right = new Node(25);
    return root;
}

int main() {
    Node* root = createSampleTree();
    cout << "Maximum sum of nodes in the binary tree such that no two nodes are adjacent to each other: " << maxSumOfNonAdjacentNodes(root) << endl;
    return 0;
}
