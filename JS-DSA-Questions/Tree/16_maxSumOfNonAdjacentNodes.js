// Maximum sum of nodes in a binary tree such that no two selected nodes are adjacent
// (parent-child). This is "House Robber III".

// Video link : https://www.youtube.com/watch?v=S68tDCB4mTY

// For each node there are two choices:
//   INCLUDE it (then its children must be excluded) or EXCLUDE it (children free to choose).

// =====================================================================================
// APPROACH 1: Pure recursion — O(2^n) (overlapping subproblems)
// =====================================================================================
// include = node.val + solve(grandchildren); exclude = solve(children). return max(include, exclude).
function maxSumBruteForce(root) {
  function solve(node) {
    if (node === null) return 0;

    let include = node.val;
    if (node.left) {
      include += solve(node.left.left);
      include += solve(node.left.right);
    }
    if (node.right) {
      include += solve(node.right.left);
      include += solve(node.right.right);
    }

    const exclude = solve(node.left) + solve(node.right);
    return Math.max(include, exclude);
  }
  return solve(root);
}

// =====================================================================================
// APPROACH 2 (best): each call returns { include, exclude } — O(n) time, O(h) space
// =====================================================================================
// include = node.val + left.exclude + right.exclude  (children must be excluded)
// exclude = max(left.include, left.exclude) + max(right.include, right.exclude)
// answer = max(root.include, root.exclude)
//
// JavaScript note: C++ returned pair<int,int>. Here we return an object { include, exclude }.
class TreeNode {
  constructor(x) {
    this.val = x;
    this.left = null;
    this.right = null;
  }
}

function maxSum(root) {
  function solve(node) {
    if (node === null) return { include: 0, exclude: 0 };

    const left = solve(node.left);
    const right = solve(node.right);

    const include = node.val + left.exclude + right.exclude;
    const exclude =
      Math.max(left.include, left.exclude) + Math.max(right.include, right.exclude);

    return { include, exclude };
  }

  const result = solve(root);
  return Math.max(result.include, result.exclude);
}

// Test tree:
//         10
//        /  \
//       1    2
//      / \
//     3   4
const root = new TreeNode(10);
root.left = new TreeNode(1);
root.right = new TreeNode(2);
root.left.left = new TreeNode(3);
root.left.right = new TreeNode(4);

console.log("Brute Force:", maxSumBruteForce(root)); // 17
console.log("Optimized:  ", maxSum(root)); // 17 (select 10 + 3 + 4)

// | Approach          | Time    | Space  |
// |-------------------|---------|--------|
// | Brute Force       | O(2^n)  | O(h)   |
// | Memoization       | O(n)    | O(n)   |
// | Optimized (pair)  | O(n)    | O(h)   |  ← best
