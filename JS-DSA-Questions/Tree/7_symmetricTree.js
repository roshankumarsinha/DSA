// Check whether a binary tree is a mirror of itself (symmetric around its center).

// A tree is symmetric if the left subtree is a MIRROR of the right subtree:
//   - their roots match, AND
//   - left.left mirrors right.right, AND left.right mirrors right.left.

// =====================================================================================
// SOLUTION 1: Recursive
// =====================================================================================
// isMirror(t1, t2):
//   - both null → true
//   - one null → false
//   - values equal AND isMirror(t1.left, t2.right) AND isMirror(t1.right, t2.left)
// Time O(n), Space O(h).

class TreeNode {
  constructor(x) {
    this.val = x;
    this.left = null;
    this.right = null;
  }
}

function isMirror(t1, t2) {
  if (t1 === null && t2 === null) return true;
  if (t1 === null || t2 === null) return false;
  return (
    t1.val === t2.val &&
    isMirror(t1.left, t2.right) &&
    isMirror(t1.right, t2.left)
  );
}

function isSymmetric(root) {
  if (root === null) return true;
  return isMirror(root.left, root.right);
}

// =====================================================================================
// SOLUTION 2: Iterative with a queue
// =====================================================================================
// Push mirror pairs; for each pair check equality and enqueue (t1.left, t2.right) and
// (t1.right, t2.left). Time O(n), Space O(n).
// JavaScript note: a plain array is the queue (push/shift).
function isSymmetricIterative(root) {
  if (root === null) return true;

  const q = [root.left, root.right];

  while (q.length > 0) {
    const t1 = q.shift();
    const t2 = q.shift();

    if (t1 === null && t2 === null) continue;
    if (t1 === null || t2 === null) return false;
    if (t1.val !== t2.val) return false;

    q.push(t1.left, t2.right);
    q.push(t1.right, t2.left);
  }

  return true;
}

// Symmetric tree:
//         1
//        / \
//       2   2
//      / \ / \
//     3  4 4  3
const root1 = new TreeNode(1);
root1.left = new TreeNode(2);
root1.right = new TreeNode(2);
root1.left.left = new TreeNode(3);
root1.left.right = new TreeNode(4);
root1.right.left = new TreeNode(4);
root1.right.right = new TreeNode(3);

console.log("Recursive:", isSymmetric(root1) ? "Symmetric" : "Not Symmetric");
console.log("Iterative:", isSymmetricIterative(root1) ? "Symmetric" : "Not Symmetric");

// Non-symmetric tree:
const root2 = new TreeNode(1);
root2.left = new TreeNode(2);
root2.right = new TreeNode(2);
root2.left.right = new TreeNode(3);
root2.right.right = new TreeNode(3);
console.log("Recursive:", isSymmetric(root2) ? "Symmetric" : "Not Symmetric");
