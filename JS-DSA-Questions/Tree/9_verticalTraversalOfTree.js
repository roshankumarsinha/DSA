// Vertical order traversal of a binary tree.
// Nodes are grouped by horizontal distance (column) from left to right. Within a column, order by
// depth (top to bottom); ties at the same (column, depth) go left to right.

// Notes : https://takeuforward.org/data-structure/vertical-order-traversal-of-binary-tree/

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
// Vertical Order: [[4], [2], [1, 5], [3], [6]] → flattened: 4 2 1 5 3 6

// Approach (BFS with coordinates):
// - Root at (hd=0, depth=0). Left child → hd-1, right child → hd+1; depth increases by 1.
// - Bucket node values by hd, then by depth. Output columns in increasing hd order.

// JavaScript note: C++ used map<int, map<int, vector<int>>> which auto-sorts keys. JS Maps preserve
// insertion order, NOT numeric order, so we collect into a Map and then sort the hd keys (and the
// depth keys) numerically ourselves before flattening.
class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function verticalTraversal(root) {
  const result = [];
  if (root === null) return result;

  // Map<hd, Map<depth, number[]>>
  const nodes = new Map();

  // Queue of { node, hd, depth }
  const q = [{ node: root, hd: 0, depth: 0 }];

  while (q.length > 0) {
    const { node, hd, depth } = q.shift();

    if (!nodes.has(hd)) nodes.set(hd, new Map());
    const depthMap = nodes.get(hd);
    if (!depthMap.has(depth)) depthMap.set(depth, []);
    depthMap.get(depth).push(node.data);

    if (node.left) q.push({ node: node.left, hd: hd - 1, depth: depth + 1 });
    if (node.right) q.push({ node: node.right, hd: hd + 1, depth: depth + 1 });
  }

  // Emit columns in increasing horizontal distance, then increasing depth
  const sortedHds = [...nodes.keys()].sort((a, b) => a - b);
  for (const hd of sortedHds) {
    const depthMap = nodes.get(hd);
    const sortedDepths = [...depthMap.keys()].sort((a, b) => a - b);
    for (const depth of sortedDepths) {
      for (const val of depthMap.get(depth)) {
        result.push(val);
      }
    }
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

console.log("Vertical Traversal:", verticalTraversal(createSampleTree()).join(" ")); // 4 2 1 5 3 6
