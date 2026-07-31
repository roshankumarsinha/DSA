// Convert a Complete Binary Search Tree into a Min-Heap.

// Approach:
// 1. Inorder traversal of the BST → elements in sorted (ascending) order.
// 2. Pre-order traversal to write those values back. Pre-order visits parent before children, so
//    assigning ascending values in pre-order guarantees each parent <= its children (min-heap),
//    while keeping the tree's complete structure.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function inorderTraversal(root, elements) {
  if (root === null) return;
  inorderTraversal(root.left, elements);
  elements.push(root.data);
  inorderTraversal(root.right, elements);
}

// JavaScript note: C++ passed the index by reference (int&). JS numbers are passed by value, so we
// wrap the index in an object { i } so the recursion shares and advances it.
function assignValuesPreOrder(root, elements, idx) {
  if (root === null) return;
  root.data = elements[idx.i++];
  assignValuesPreOrder(root.left, elements, idx);
  assignValuesPreOrder(root.right, elements, idx);
}

function convertBSTtoMinHeap(root) {
  const elements = [];
  inorderTraversal(root, elements);
  assignValuesPreOrder(root, elements, { i: 0 });
}

function createSampleBST() {
  const root = new Node(4);
  root.left = new Node(2);
  root.right = new Node(6);
  root.left.left = new Node(1);
  root.left.right = new Node(3);
  root.right.left = new Node(5);
  root.right.right = new Node(7);
  return root;
}

function printPreOrder(root, out = []) {
  if (root === null) return out;
  out.push(root.data);
  printPreOrder(root.left, out);
  printPreOrder(root.right, out);
  return out;
}

const root = createSampleBST();
console.log("Original BST (Pre-Order):", printPreOrder(root).join(" "));
convertBSTtoMinHeap(root);
console.log("Converted Min-Heap (Pre-Order):", printPreOrder(root).join(" ")); // 1 2 4 5 3 6 7
