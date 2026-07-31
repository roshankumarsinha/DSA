// Flatten a BST into a sorted linked list (right-skewed tree: all left pointers null, nodes in
// inorder sequence).

// Approach: inorder traversal (gives sorted values) → build a right-linked list.
// Time: O(N). Space: O(N).

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

function flattenBSTToSortedLL(root) {
  const elements = [];
  inorderTraversal(root, elements); // sorted

  let head = null;
  let tail = null;

  for (const val of elements) {
    const newNode = new Node(val); // left stays null
    if (head === null) {
      head = newNode;
      tail = newNode;
    } else {
      tail.right = newNode;
      tail = newNode;
    }
  }

  return head;
}

function createSampleBST() {
  const root = new Node(5);
  root.left = new Node(3);
  root.right = new Node(7);
  root.left.left = new Node(2);
  root.left.right = new Node(4);
  root.right.right = new Node(8);
  return root;
}

const root = createSampleBST();
const head = flattenBSTToSortedLL(root);

const out = [];
let current = head;
while (current !== null) {
  out.push(current.data);
  current = current.right;
}
console.log("Flattened BST to Sorted Linked List:", out.join(" ")); // 2 3 4 5 7 8
