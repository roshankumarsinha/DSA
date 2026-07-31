// Find the Kth ancestor of a node in a binary tree (the Kth parent moving upward).

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
// 2nd ancestor of 4: 4 → 2 (1st) → 1 (2nd). Answer: 1.

// Approach (recursion + backtracking):
// - Find the target node (return it up the call stack).
// - As the found node bubbles up, decrement k at each ancestor. When k hits 0, that ancestor is
//   the answer; lock it (set k to a huge value) so it isn't overwritten.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ passed k by reference (int&) and used INT_MAX to "lock" the answer. Here we
// carry k in a state object and use Infinity as the lock value.
function solve(root, node, state) {
  if (root === null) return null;

  if (root.data === node) return root;

  const leftAns = solve(root.left, node, state);
  const rightAns = solve(root.right, node, state);

  if (leftAns !== null && rightAns === null) {
    state.k--;
    if (state.k === 0) {
      state.k = Infinity; // lock this node as the answer
      return root;
    }
    return leftAns;
  }

  if (rightAns !== null && leftAns === null) {
    state.k--;
    if (state.k === 0) {
      state.k = Infinity;
      return root;
    }
    return rightAns;
  }

  return null;
}

function kthAncestor(root, node, k) {
  const state = { k };
  const ans = solve(root, node, state);
  if (ans === null || ans.data === node) {
    return -1; // node not found, or no kth ancestor exists
  }
  return ans.data;
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  root.right.right = new Node(6);
  return root;
}

const root = createSampleTree();
console.log("The 2nd ancestor of Node 4 is:", kthAncestor(root, 4, 2)); // 1
