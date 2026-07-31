// Find the kth smallest element in a Binary Search Tree.

// Approach:
// 1. Inorder traversal visits BST nodes in ascending order.
// 2. Keep a counter of visited nodes; when it reaches k, that node's value is the answer.
// Time: O(N). Space: O(H).

// To find the kth LARGEST: do a reverse inorder traversal, or find the (n - k + 1)th smallest.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ passed counter and result by reference (int&). JS numbers are by value, so
// we carry mutable state in an object `state = { counter, result }`.
function inorder(root, k, state) {
  if (root === null || state.counter > k) return;

  inorder(root.left, k, state);

  state.counter++;
  if (state.counter === k) {
    state.result = root.data;
    return;
  }

  inorder(root.right, k, state);
}

function kthSmallestElement(root, k) {
  const state = { counter: 0, result: -1 };
  inorder(root, k, state);
  return state.result;
}

function createSampleBST() {
  const root = new Node(50);
  root.left = new Node(30);
  root.right = new Node(70);
  root.left.left = new Node(20);
  root.left.left.left = new Node(10);
  root.left.right = new Node(40);
  root.right.right = new Node(80);
  return root;
}

const root = createSampleBST();
console.log("The kth smallest element in the BST is:", kthSmallestElement(root, 3)); // 30
