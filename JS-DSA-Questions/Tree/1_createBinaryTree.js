// Create a Binary Tree and traverse it in various orders.
// Creation notes : https://takeuforward.org/binary-tree/binary-tree-representation-in-c/

// JavaScript note: the C++ version read node values from cin recursively (-1 means "no node").
// Since JS has no simple synchronous stdin, we build the tree from an array of values in preorder,
// using -1 as the null marker. We use a shared cursor object { i } (C++ passed an int& implicitly
// via recursion order).
class TreeNode {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// Build a tree from a preorder value list where -1 denotes a null child.
function buildTree(values, idx = { i: 0 }) {
  if (idx.i >= values.length) return null;
  const data = values[idx.i++];
  if (data === -1) return null;

  const root = new TreeNode(data);
  root.left = buildTree(values, idx);
  root.right = buildTree(values, idx);
  return root;
}

// Level Order Traversal (BFS). Uses a plain array as a queue.
// Time O(N), Space O(N).
function levelOrderTraversal(root) {
  if (root === null) return [];
  const q = [root];
  const out = [];
  while (q.length > 0) {
    const temp = q.shift();
    out.push(temp.data);
    if (temp.left) q.push(temp.left);
    if (temp.right) q.push(temp.right);
  }
  return out;
}

// InOrder: Left, Node, Right
function inOrderTraversal(root, out = []) {
  if (root === null) return out;
  inOrderTraversal(root.left, out);
  out.push(root.data);
  inOrderTraversal(root.right, out);
  return out;
}

// PreOrder: Node, Left, Right
function preOrderTraversal(root, out = []) {
  if (root === null) return out;
  out.push(root.data);
  preOrderTraversal(root.left, out);
  preOrderTraversal(root.right, out);
  return out;
}

// PostOrder: Left, Right, Node
function postOrderTraversal(root, out = []) {
  if (root === null) return out;
  postOrderTraversal(root.left, out);
  postOrderTraversal(root.right, out);
  out.push(root.data);
  return out;
}

// Count leaf nodes (a node with no children)
function countLeafNodes(root) {
  if (root === null) return 0;
  if (root.left === null && root.right === null) return 1;
  return countLeafNodes(root.left) + countLeafNodes(root.right);
}

// Driver: preorder with -1 nulls building
//          1
//         / \
//        3   5
//       / \  /
//      7  11 17
const root = buildTree([1, 3, 7, -1, -1, 11, -1, -1, 5, 17, -1, -1, -1]);
console.log("Level Order Traversal :", levelOrderTraversal(root).join(" ")); // 1 3 5 7 11 17
console.log("InOrder Traversal :", inOrderTraversal(root).join(" ")); // 7 3 11 1 17 5
console.log("PreOrder Traversal :", preOrderTraversal(root).join(" ")); // 1 3 7 11 5 17
console.log("PostOrder Traversal :", postOrderTraversal(root).join(" ")); // 7 11 3 17 5 1
console.log("Number of Leaf Nodes :", countLeafNodes(root)); // 3
