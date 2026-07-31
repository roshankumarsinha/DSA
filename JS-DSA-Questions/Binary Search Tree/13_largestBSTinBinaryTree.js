// Find the size of the largest BST within a binary tree.
// Video from Striver: https://www.youtube.com/watch?v=X0oXMdtUDwo

// Approach (postorder / bottom-up):
// For each node compute { size, min, max, isBST }:
// - A node forms a BST if both subtrees are BSTs and node.data > left.max and node.data < right.min.
// - Track the maximum BST size seen.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used INT_MAX/INT_MIN for the null-subtree sentinels and passed maxSize by
// reference. Here we use Infinity/-Infinity and carry maxSize in an object { value }.
function largestBST(root, state) {
  // Null subtree: size 0, min = +Inf, max = -Inf, isBST true (so a leaf's parent compares cleanly)
  if (root === null) {
    return { size: 0, min: Infinity, max: -Infinity, isBST: true };
  }

  const leftInfo = largestBST(root.left, state);
  const rightInfo = largestBST(root.right, state);

  const currInfo = {
    size: leftInfo.size + rightInfo.size + 1,
    min: Math.min(root.data, leftInfo.min),
    max: Math.max(root.data, rightInfo.max),
    isBST: false,
  };

  if (leftInfo.isBST && rightInfo.isBST && root.data > leftInfo.max && root.data < rightInfo.min) {
    currInfo.isBST = true;
    state.value = Math.max(state.value, currInfo.size);
  }

  return currInfo;
}

function largestBSTSize(root) {
  const state = { value: 0 };
  largestBST(root, state);
  return state.value;
}

function createSampleBinaryTree() {
  const root = new Node(10);
  root.left = new Node(5);
  root.right = new Node(15);
  root.left.left = new Node(1);
  root.left.right = new Node(8);
  root.right.right = new Node(7);
  return root;
}

const root = createSampleBinaryTree();
console.log("Size of the largest BST in the binary tree:", largestBSTSize(root)); // 3
