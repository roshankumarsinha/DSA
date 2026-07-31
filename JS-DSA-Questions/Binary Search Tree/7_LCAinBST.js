// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.
// The LCA is the lowest node that has both p and q as descendants (a node can be its own descendant).

// Approach (recursive, using BST ordering):
// - If both p and q are less than root, the LCA is in the left subtree.
// - If both are greater than root, the LCA is in the right subtree.
// - Otherwise (they split, or one equals root), root is the LCA.
// Time: O(H). Space: O(H) recursion (O(1) iterative).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function LCAinBST(root, p, q) {
  if (root === null) return null;

  if (root.data > p.data && root.data > q.data) {
    return LCAinBST(root.left, p, q);
  }
  if (root.data < p.data && root.data < q.data) {
    return LCAinBST(root.right, p, q);
  }
  return root;
}

// Iterative version (O(1) space):
// function LCAinBST(root, p, q) {
//   while (root !== null) {
//     if (root.data > p.data && root.data > q.data) root = root.left;
//     else if (root.data < p.data && root.data < q.data) root = root.right;
//     else return root;
//   }
//   return null;
// }

function createSampleTree() {
  const root = new Node(6);
  root.left = new Node(2);
  root.right = new Node(8);
  root.left.left = new Node(0);
  root.left.right = new Node(4);
  root.left.right.left = new Node(3);
  root.left.right.right = new Node(5);
  root.right.left = new Node(7);
  root.right.right = new Node(9);
  return root;
}

const root = createSampleTree();
const p = root.left.right; // 4
const q = root.left; // 2
const lca = LCAinBST(root, p, q);
console.log(`LCA of ${p.data} and ${q.data} is ${lca.data}`); // 2
