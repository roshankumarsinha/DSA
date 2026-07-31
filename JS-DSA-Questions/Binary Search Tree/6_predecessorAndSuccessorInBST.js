// Find the Inorder Predecessor and Successor of a key in a BST.

// Approach 2 (iterative, O(H) time, O(1) space):
// - Walk down the tree. When current < key, current is a predecessor candidate; go right.
//   When current > key, current is a successor candidate; go left.
// - When the key is found: predecessor is the max of the left subtree, successor is the min of the
//   right subtree (if those subtrees exist).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ passed predecessor/successor by reference (Node*&). Here we return them in
// an object { predecessor, successor } instead.
function findPredecessorAndSuccessor(root, key) {
  let predecessor = null;
  let successor = null;

  while (root !== null) {
    if (root.data < key) {
      predecessor = root; // possible predecessor
      root = root.right;
    } else if (root.data > key) {
      successor = root; // possible successor
      root = root.left;
    } else {
      // key found
      if (root.left) {
        let p = root.left;
        while (p.right) p = p.right; // rightmost of left subtree
        predecessor = p;
      }
      if (root.right) {
        let s = root.right;
        while (s.left) s = s.left; // leftmost of right subtree
        successor = s;
      }
      break;
    }
  }

  return { predecessor, successor };
}

function createSampleTree() {
  const root = new Node(20);
  root.left = new Node(8);
  root.right = new Node(22);
  root.left.left = new Node(4);
  root.left.right = new Node(12);
  root.left.right.left = new Node(10);
  root.left.right.right = new Node(14);
  return root;
}

const root = createSampleTree();
const key = 10;
const { predecessor, successor } = findPredecessorAndSuccessor(root, key);
console.log(`Inorder Predecessor of ${key} is:`, predecessor ? predecessor.data : "NULL"); // 8
console.log(`Inorder Successor of ${key} is:`, successor ? successor.data : "NULL"); // 12
