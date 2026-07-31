// Convert a normal (possibly skewed) BST into a height-balanced BST.

// Approach:
// 1. Inorder traversal → sorted array of values.
// 2. Build a balanced BST by recursively choosing the middle element as the root, so the array
//    splits into equal-sized left and right halves.

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

function buildBalancedBST(elements, start, end) {
  if (start > end) return null;

  const mid = start + Math.floor((end - start) / 2);
  const root = new Node(elements[mid]);

  root.left = buildBalancedBST(elements, start, mid - 1);
  root.right = buildBalancedBST(elements, mid + 1, end);

  return root;
}

function convertToBalancedBST(root) {
  const elements = [];
  inorderTraversal(root, elements);
  return buildBalancedBST(elements, 0, elements.length - 1);
}

// Skewed BST: 1 -> 2 -> 3 -> 4 -> 5 (all right children)
function createSampleBST() {
  const root = new Node(1);
  root.right = new Node(2);
  root.right.right = new Node(3);
  root.right.right.right = new Node(4);
  root.right.right.right.right = new Node(5);
  return root;
}

const root = createSampleBST();
let elements = [];
inorderTraversal(root, elements);
console.log("Original BST (Inorder Traversal):", elements.join(" "));

const balancedRoot = convertToBalancedBST(root);
elements = [];
inorderTraversal(balancedRoot, elements);
console.log("Balanced BST (Inorder Traversal):", elements.join(" "));
