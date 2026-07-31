// Boundary traversal of a binary tree, in three parts:
// 1. Left boundary (excluding leaves), top to bottom.
// 2. Leaf nodes, left to right.
// 3. Right boundary (excluding leaves), bottom to top (reversed).

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
//       / \
//      7   8
// Boundary: 1 2 4 5 7 8 6 3

// Time: O(n). Space: O(n) recursion.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function printLeftBoundary(root, result) {
  if (root === null) return;
  if (root.left === null && root.right === null) return; // skip leaves

  result.push(root.data);
  if (root.left) {
    printLeftBoundary(root.left, result);
  } else {
    printLeftBoundary(root.right, result);
  }
}

// Leaf nodes via inorder traversal
function printLeafNodes(root, result) {
  if (root === null) return;
  printLeafNodes(root.left, result);
  if (root.left === null && root.right === null) {
    result.push(root.data);
  }
  printLeafNodes(root.right, result);
}

function printRightBoundary(root, result) {
  if (root === null) return;
  if (root.left === null && root.right === null) return; // skip leaves

  if (root.right) {
    printRightBoundary(root.right, result);
  } else {
    printRightBoundary(root.left, result);
  }
  result.push(root.data); // push AFTER recursion → reversed (bottom-up)
}

function boundaryTraversal(root) {
  const result = [];
  if (root === null) return result;

  result.push(root.data);
  printLeftBoundary(root.left, result);
  printLeafNodes(root, result);
  printRightBoundary(root.right, result);

  return result;
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  root.right.right = new Node(6);
  root.left.right.left = new Node(7);
  root.left.right.right = new Node(8);
  return root;
}

console.log("Boundary Traversal:", boundaryTraversal(createSampleTree()).join(" ")); // 1 2 4 5 7 8 6 3
