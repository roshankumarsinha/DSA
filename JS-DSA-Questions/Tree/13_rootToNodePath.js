// Find the path from the root to a given node in a binary tree.
// This is a foundational building block (used for LCA, node distance, etc.).

// Notes : https://takeuforward.org/data-structure/print-root-to-node-path-in-a-binary-tree/

// Intuition (recursive with backtracking):
// 1. Push the current node onto the path.
// 2. If it's the target, return true.
// 3. Recurse into left/right; if either finds the target, return true.
// 4. Otherwise pop (backtrack) and return false.
// Time O(N), Space O(H).

class TreeNode {
  constructor(x) {
    this.val = x;
    this.left = null;
    this.right = null;
  }
}

function getPath(root, arr, x) {
  if (!root) return false;

  arr.push(root.val);

  if (root.val === x) return true;

  if (getPath(root.left, arr, x) || getPath(root.right, arr, x)) {
    return true;
  }

  arr.pop(); // backtrack
  return false;
}

function solve(root, target) {
  const arr = [];
  if (root === null) return arr;
  getPath(root, arr, target);
  return arr;
}

// Build:
//        3
//       / \
//      5   1
//     / \ / \
//    6  2 0  8
//      / \
//     7   4
const root = new TreeNode(3);
root.left = new TreeNode(5);
root.right = new TreeNode(1);
root.left.left = new TreeNode(6);
root.left.right = new TreeNode(2);
root.right.left = new TreeNode(0);
root.right.right = new TreeNode(8);
root.left.right.left = new TreeNode(7);
root.left.right.right = new TreeNode(4);

const targetLeafValue = 7;
const path = solve(root, targetLeafValue);
console.log(`Path from root to node with value ${targetLeafValue}: ${path.join(" -> ")}`); // 3 -> 5 -> 2 -> 7
