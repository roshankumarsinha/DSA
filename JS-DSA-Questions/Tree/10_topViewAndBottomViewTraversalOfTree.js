// Top View and Bottom View of a binary tree.
// Top View: the first node seen at each horizontal distance (column) from the top.
// Bottom View: the last node seen at each horizontal distance.

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
// Top View:    4 2 1 3 6
// Bottom View: 4 2 5 3 6

// Approach (BFS with horizontal distance):
// - Root hd = 0; left child hd-1, right child hd+1.
// - Top View: record a node only the FIRST time an hd is seen.
// - Bottom View: OVERWRITE the node each time an hd is seen (last wins).
// Output columns in increasing hd order.

// JavaScript note: C++ used std::map (auto-sorted keys). JS Map preserves insertion order, so we
// sort the hd keys numerically before emitting.
class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function topView(root) {
  const result = [];
  if (root === null) return result;

  const nodes = new Map(); // hd -> value (first seen)
  const q = [{ node: root, hd: 0 }];

  while (q.length > 0) {
    const { node, hd } = q.shift();
    if (!nodes.has(hd)) {
      nodes.set(hd, node.data); // only the first node at this hd
    }
    if (node.left) q.push({ node: node.left, hd: hd - 1 });
    if (node.right) q.push({ node: node.right, hd: hd + 1 });
  }

  for (const hd of [...nodes.keys()].sort((a, b) => a - b)) {
    result.push(nodes.get(hd));
  }
  return result;
}

function bottomView(root) {
  const result = [];
  if (root === null) return result;

  const nodes = new Map(); // hd -> value (last seen)
  const q = [{ node: root, hd: 0 }];

  while (q.length > 0) {
    const { node, hd } = q.shift();
    nodes.set(hd, node.data); // overwrite → last node at this hd wins
    if (node.left) q.push({ node: node.left, hd: hd - 1 });
    if (node.right) q.push({ node: node.right, hd: hd + 1 });
  }

  for (const hd of [...nodes.keys()].sort((a, b) => a - b)) {
    result.push(nodes.get(hd));
  }
  return result;
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
console.log("Top View Traversal:", topView(root).join(" ")); // 4 2 1 3 6
console.log("Bottom View Traversal:", bottomView(root).join(" ")); // 4 2 5 3 6
