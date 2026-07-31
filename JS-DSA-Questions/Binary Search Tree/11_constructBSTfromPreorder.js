// Construct a Binary Search Tree from a given preorder traversal.

// Video from Striver: https://www.youtube.com/watch?v=UmJT3j26t1I

// Approach 2 (bounds, O(N)):
// - The first preorder element is the root. As we recurse, each node must fit within a valid
//   (lower, upper) range. When the current value falls outside the range, that subtree ends.
// - Left subtree: (lower, root.data). Right subtree: (root.data, upper).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ passed `index` by reference (int&). Here we carry it in an object { i } so
// the recursion advances a shared cursor. INT_MIN/INT_MAX become -Infinity/Infinity.
function constructBSTFromPreorder(preorder, idx, lower, upper) {
  if (idx.i >= preorder.length) return null;

  if (preorder[idx.i] < lower || preorder[idx.i] > upper) {
    return null;
  }

  const root = new Node(preorder[idx.i]);
  idx.i++;

  root.left = constructBSTFromPreorder(preorder, idx, lower, root.data);
  root.right = constructBSTFromPreorder(preorder, idx, root.data, upper);

  return root;
}

function constructBSTFromPreorderMain(preorder) {
  return constructBSTFromPreorder(preorder, { i: 0 }, -Infinity, Infinity);
}

function inorderTraversal(root, out = []) {
  if (root === null) return out;
  inorderTraversal(root.left, out);
  out.push(root.data);
  inorderTraversal(root.right, out);
  return out;
}

const preorder = [10, 5, 1, 7, 40, 50];
const root = constructBSTFromPreorderMain(preorder);
console.log("Inorder Traversal of the constructed BST:", inorderTraversal(root).join(" ")); // 1 5 7 10 40 50
