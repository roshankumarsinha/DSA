// Validate a Binary Search Tree.

// Approach 1: inorder traversal is sorted for a valid BST → collect and check sortedness. O(N)/O(N).
// Approach 2 (used here): recursion with a valid [min, max] range for each node. O(N) time, O(H) space.
//   - Left child must be < current and > min; right child must be > current and < max.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used LLONG_MIN / LLONG_MAX as the initial bounds. In JS we use
// -Infinity / Infinity, which cleanly represent unbounded limits for any number.
function isValidBST(root, minVal, maxVal) {
  if (root === null) return true;

  if (root.data >= minVal && root.data <= maxVal) {
    return (
      isValidBST(root.left, minVal, root.data) &&
      isValidBST(root.right, root.data, maxVal)
    );
  }
  return false;
}

function createSampleBST() {
  const root = new Node(5);
  root.left = new Node(3);
  root.right = new Node(7);
  root.left.left = new Node(2);
  root.left.right = new Node(4);
  root.right.left = new Node(6);
  root.right.right = new Node(8);
  return root;
}

const root = createSampleBST();
console.log(isValidBST(root, -Infinity, Infinity) ? "The given tree is a valid BST." : "The given tree is not a valid BST.");
