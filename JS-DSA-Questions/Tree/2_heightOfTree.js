// Find the height of a binary tree.
// (Here "height" counts nodes on the longest root-to-leaf path; an empty tree has height 0.)

// Approach 1: Recursive DFS
// height = 1 + max(height(left), height(right)); base case: null → 0. O(N) time, O(H) space.

// Approach 2: Iterative BFS (level-order), counting the number of levels. O(N) time, O(N) space.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function heightOfTree(root) {
  if (root === null) return 0;
  const leftHeight = heightOfTree(root.left);
  const rightHeight = heightOfTree(root.right);
  return 1 + Math.max(leftHeight, rightHeight);
}

function heightOfTreeIterative(root) {
  if (root === null) return 0;

  const q = [root];
  let height = 0;

  while (q.length > 0) {
    const levelSize = q.length; // nodes at the current level
    height++;
    for (let i = 0; i < levelSize; i++) {
      const current = q.shift();
      if (current.left) q.push(current.left);
      if (current.right) q.push(current.right);
    }
  }

  return height;
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
console.log("Height of the tree :", heightOfTree(root)); // 3
console.log("Height of the tree (Iterative) :", heightOfTreeIterative(root)); // 3
