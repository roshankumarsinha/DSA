// Merge two BSTs into a single balanced BST.

// Approach 1 (arrays):
// 1. Inorder traversal of each BST → two sorted arrays.
// 2. Merge the two sorted arrays.
// 3. Build a balanced BST from the merged sorted array (middle element as root).
// Time: O(N + M). Space: O(N + M).

// Approach 2 (doubly linked lists, O(h1 + h2) space) is described in comments at the bottom.

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

function mergeArrays(a, b) {
  const result = [];
  let i = 0;
  let j = 0;
  while (i < a.length && j < b.length) {
    if (a[i] < b[j]) result.push(a[i++]);
    else result.push(b[j++]);
  }
  while (i < a.length) result.push(a[i++]);
  while (j < b.length) result.push(b[j++]);
  return result;
}

function buildBalancedBST(elements, start, end) {
  if (start > end) return null;
  const mid = start + Math.floor((end - start) / 2);
  const root = new Node(elements[mid]);
  root.left = buildBalancedBST(elements, start, mid - 1);
  root.right = buildBalancedBST(elements, mid + 1, end);
  return root;
}

function mergeBSTs(root1, root2) {
  const e1 = [];
  const e2 = [];
  inorderTraversal(root1, e1);
  inorderTraversal(root2, e2);
  const merged = mergeArrays(e1, e2);
  return buildBalancedBST(merged, 0, merged.length - 1);
}

function createSampleBST1() {
  const root = new Node(2);
  root.left = new Node(1);
  root.right = new Node(4);
  return root;
}

function createSampleBST2() {
  const root = new Node(6);
  root.left = new Node(5);
  root.right = new Node(7);
  return root;
}

const mergedRoot = mergeBSTs(createSampleBST1(), createSampleBST2());
const out = [];
inorderTraversal(mergedRoot, out);
console.log("Merged BST (Inorder):", out.join(" ")); // 1 2 4 5 6 7

// Approach 2 outline: convert each BST to a sorted doubly linked list via inorder (left = prev,
// right = next), merge the two sorted DLLs, then build a balanced BST from the middle of the DLL.
// This avoids the extra arrays, using only O(h1 + h2) recursion space.
