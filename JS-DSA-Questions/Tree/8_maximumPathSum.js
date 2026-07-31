// Maximum Path Sum in a Binary Tree.
// A path may start and end at any nodes, moving only along parent↔child edges, using each node once.
// Find the maximum possible sum of node values along any such path.

// TUF Notes : https://takeuforward.org/data-structure/maximum-sum-path-in-binary-tree

// Example:
//       -10
//       /  \
//      9   20
//          / \
//         15  7
// Maximum Path Sum = 15 + 20 + 7 = 42

// Key idea (DFS):
// At each node, the best path that "turns" through it is left + node.val + right (update the global
// answer with this). But only ONE side can be extended upward to the parent, so we RETURN
// node.val + max(left, right). Negative child contributions are clamped to 0 (ignored).

// JavaScript note: C++ used a class member `maxSum` initialized to INT_MIN. Here we carry it in a
// closure variable initialized to -Infinity.
class TreeNode {
  constructor(x) {
    this.val = x;
    this.left = null;
    this.right = null;
  }
}

function maxPathSum(root) {
  let maxSum = -Infinity;

  function dfs(node) {
    if (node === null) return 0;

    const left = Math.max(0, dfs(node.left)); // clamp negatives to 0
    const right = Math.max(0, dfs(node.right));

    // Best path that turns through this node
    const currentPath = left + node.val + right;
    maxSum = Math.max(maxSum, currentPath);

    // Return the best single-side path to the parent
    return node.val + Math.max(left, right);
  }

  dfs(root);
  return maxSum;
}

function createSampleTree() {
  const root = new TreeNode(-10);
  root.left = new TreeNode(9);
  root.right = new TreeNode(20);
  root.right.left = new TreeNode(15);
  root.right.right = new TreeNode(7);
  return root;
}

console.log("Maximum Path Sum:", maxPathSum(createSampleTree())); // 42
