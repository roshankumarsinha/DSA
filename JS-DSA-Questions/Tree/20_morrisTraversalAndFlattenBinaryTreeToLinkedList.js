// Morris Traversal — an in-place tree traversal using O(1) extra space (no recursion or stack).
// It temporarily creates "threads" (a rightmost node's right pointer → its inorder successor) and
// removes them once used.

// Why Morris? O(1) auxiliary space and O(N) time.

// Inorder Morris Traversal:
// Step 1: Start at the root.
// Step 2: If the current node has no left child → record it, move right.
// Step 3: If it has a left child, find the inorder predecessor (rightmost node of the left subtree):
//    a. If the predecessor's right is null → set it to current (thread), move left.
//    b. If the predecessor's right is current → thread already exists (we've finished the left
//       subtree): remove the thread, record current, move right.
//
// For PREORDER: record the node when you CREATE the thread (in case 3a) instead of in case 3b.

class TreeNode {
  constructor(x) {
    this.val = x;
    this.left = null;
    this.right = null;
  }
}

function getInorder(root) {
  const inorder = [];
  let cur = root;

  while (cur !== null) {
    if (cur.left === null) {
      inorder.push(cur.val);
      cur = cur.right;
    } else {
      // Find the inorder predecessor
      let prev = cur.left;
      while (prev.right && prev.right !== cur) {
        prev = prev.right;
      }

      if (prev.right === null) {
        prev.right = cur; // create thread
        // For preorder: inorder.push(cur.val) here instead of below
        cur = cur.left;
      } else {
        prev.right = null; // remove thread
        inorder.push(cur.val); // record on the way back up
        cur = cur.right;
      }
    }
  }

  return inorder;
}

// Build:
//        1
//       / \
//      2   3
//     / \
//    4   5
//         \
//          6
const root = new TreeNode(1);
root.left = new TreeNode(2);
root.right = new TreeNode(3);
root.left.left = new TreeNode(4);
root.left.right = new TreeNode(5);
root.left.right.right = new TreeNode(6);

console.log("Binary Tree Morris Inorder Traversal:", getInorder(root).join(" ")); // 4 2 5 6 1 3

// Related idea — "Flatten Binary Tree to Linked List" uses the same threading trick to rewire the
// tree into a right-skewed list following preorder.
// See: https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/
