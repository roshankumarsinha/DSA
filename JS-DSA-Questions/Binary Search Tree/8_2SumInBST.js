// Determine whether two nodes in a BST sum to a given target k.

// Approach 1 (Inorder + Two Pointers):
// 1. Inorder traversal of a BST yields a sorted array.
// 2. Use two pointers (left from the start, right from the end):
//    - sum === k → found
//    - sum < k → move left right (increase sum)
//    - sum > k → move right left (decrease sum)
// Time: O(N). Space: O(N) for the array.

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

function findTarget(root, k) {
  const elements = [];
  inorderTraversal(root, elements); // sorted

  let left = 0;
  let right = elements.length - 1;

  while (left < right) {
    const sum = elements[left] + elements[right];
    if (sum === k) {
      return true;
    } else if (sum < k) {
      left++;
    } else {
      right--;
    }
  }
  return false;
}

function createSampleTree() {
  const root = new Node(5);
  root.left = new Node(3);
  root.right = new Node(6);
  root.left.left = new Node(2);
  root.left.right = new Node(4);
  root.right.right = new Node(7);
  return root;
}

const root = createSampleTree();
const k = 9;
console.log(
  findTarget(root, k)
    ? `There exist two elements in the BST such that their sum equals ${k}`
    : "No such pair found in the BST."
);

// Approach 2 (O(H) space): use two iterators — a normal inorder (smallest-first) and a reverse
// inorder (largest-first) — to simulate the two pointers without storing all elements.
