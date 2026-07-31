// Check if a binary tree is a Sum Tree.
// A Sum Tree: every non-leaf node's value equals the sum of ALL node values in its left and right
// subtrees. Leaf nodes are trivially sum trees.
// Example:
//        26
//       /  \
//     10    3
//    /  \     \
//   4    6     3
// 10 = 4 + 6, right "3" node's subtree sums, 26 = 10 + 3 + (4+6) + 3 → it IS a Sum Tree.

// Approach (recursive), returning { sum, isSumTree } per subtree:
// - null → { 0, true }
// - leaf → { node.data, true }
// - else valid if both children are sum trees AND node.data === leftSum + rightSum;
//   the subtree's total sum = node.data + leftSum + rightSum.
// Time: O(N). Space: O(N) recursion.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function checkSumTree(root) {
  if (root === null) {
    return { sum: 0, isSumTree: true };
  }
  if (root.left === null && root.right === null) {
    return { sum: root.data, isSumTree: true };
  }

  const left = checkSumTree(root.left);
  const right = checkSumTree(root.right);

  const isSumTree = left.isSumTree && right.isSumTree && root.data === left.sum + right.sum;

  return { sum: root.data + left.sum + right.sum, isSumTree };
}

function createSumTree() {
  const root = new Node(26);
  root.left = new Node(10);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(6);
  root.right.right = new Node(3);
  return root;
}

console.log(checkSumTree(createSumTree()).isSumTree ? "Yes, it is a Sum Tree." : "No, it is not a Sum Tree.");
