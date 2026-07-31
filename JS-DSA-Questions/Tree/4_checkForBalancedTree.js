// Check if a binary tree is height-balanced.
// Notes : https://takeuforward.org/data-structure/check-if-the-binary-tree-is-balanced-binary-tree/
// Balanced = for every node, |height(left) - height(right)| <= 1.

// Approach 1 (naive): compute height for every node → O(N^2).
// Approach 2 (optimized): one DFS returning both height and balance status → O(N).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ returned pair<int,bool> {height, isBalanced}. Here we return an object.
function isBalanced(root) {
  if (root === null) {
    return { height: 0, balanced: true };
  }

  const left = isBalanced(root.left);
  const right = isBalanced(root.right);

  const diff = Math.abs(left.height - right.height) <= 1;
  const height = Math.max(left.height, right.height) + 1;
  const balanced = left.balanced && right.balanced && diff;

  return { height, balanced };
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  root.right.left = new Node(6);
  root.right.right = new Node(7);
  return root;
}

const root = createSampleTree();
console.log(isBalanced(root).balanced ? "Tree is Balanced." : "Tree is not Balanced.");

// Cleaner alternative: a checkHeight helper that returns -1 as soon as an imbalance is found,
// short-circuiting the rest of the traversal.
