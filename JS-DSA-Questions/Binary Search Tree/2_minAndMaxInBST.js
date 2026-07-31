// Find the minimum and maximum values in a Binary Search Tree.

// Approach:
// - Minimum: the leftmost node (keep going left until left is null).
// - Maximum: the rightmost node (keep going right until right is null).
// Time: O(H) where H is the tree height. Space: O(1).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function findMin(root) {
  while (root.left !== null) {
    root = root.left;
  }
  return root.data;
}

function findMax(root) {
  while (root.right !== null) {
    root = root.right;
  }
  return root.data;
}

function createSampleBST() {
  const root = new Node(50);
  root.left = new Node(30);
  root.right = new Node(70);
  root.left.left = new Node(20);
  root.left.right = new Node(40);
  root.right.right = new Node(80);
  return root;
}

const root = createSampleBST();
console.log("Minimum value in the BST:", findMin(root)); // 20
console.log("Maximum value in the BST:", findMax(root)); // 80
