// Check if two binary trees are identical (same structure and same node values).
// Notes : https://takeuforward.org/data-structure/check-if-two-trees-are-identical/

// Approach (recursive):
// 1. Both null → identical.
// 2. One null, the other not → not identical.
// 3. Values differ → not identical.
// 4. Recursively compare left subtrees and right subtrees.
// Time: O(N). Space: O(N) recursion.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function identicalTree(root1, root2) {
  if (root1 === null && root2 === null) return true;
  if (root1 === null || root2 === null) return false;

  const left = identicalTree(root1.left, root2.left);
  const right = identicalTree(root1.right, root2.right);
  const sameValue = root1.data === root2.data;

  return left && right && sameValue;
}

function createSampleTree1() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  return root;
}

function createSampleTree2() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  return root;
}

console.log(identicalTree(createSampleTree1(), createSampleTree2()) ? "Trees are identical." : "Trees are not identical.");
