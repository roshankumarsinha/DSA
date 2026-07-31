// Lowest Common Ancestor (LCA) of two nodes in a binary tree (NOT a BST).
// The LCA is the deepest node that has both nodes as descendants.

// Notes : https://takeuforward.org/data-structure/lowest-common-ancestor-for-two-given-nodes/

// Approach (single recursive traversal):
// - If root is null, return null.
// - If root matches n1 or n2, return root.
// - Recurse left and right.
// - If both sides return non-null, root is the LCA (the two targets are in different subtrees).
// - Otherwise return whichever side is non-null.
// Time O(N), Space O(H).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function findLCA(root, n1, n2) {
  if (root === null) return null;

  if (root.data === n1 || root.data === n2) return root;

  const leftLCA = findLCA(root.left, n1, n2);
  const rightLCA = findLCA(root.right, n1, n2);

  if (leftLCA && rightLCA) return root; // targets split across subtrees → this is the LCA

  return leftLCA !== null ? leftLCA : rightLCA;
}

//        1
//       / \
//      2   3
//     / \ / \
//    4  5 6  7
const root = new Node(1);
root.left = new Node(2);
root.right = new Node(3);
root.left.left = new Node(4);
root.left.right = new Node(5);
root.right.left = new Node(6);
root.right.right = new Node(7);

console.log("LCA of 4 and 5 is:", findLCA(root, 4, 5).data); // 2
console.log("LCA of 4 and 6 is:", findLCA(root, 4, 6).data); // 1
