// Minimum time to burn a binary tree starting from a target node.
// Fire spreads to adjacent nodes (parent and children), one step per second.

// Example:
//      1
//    /   \
//   2     3
//  / \     \
// 4   5     6
//    /
//   7
// Fire starts at 5 → total time = 4 seconds.

// Approach:
// 1. Build a parent map so each node can reach its parent (BFS), and find the target node.
// 2. BFS outward from the target, visiting children and parent, counting levels (= seconds).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used unordered_map<Node*, Node*>. In JS, node objects can be used directly
// as Map keys (identity-based), so `parent` is a Map<Node, Node> and `visited` is a Set<Node>.
function buildParentMapping(root, parent, target) {
  const q = [root];
  let targetNode = null;

  while (q.length > 0) {
    const current = q.shift();
    if (current.data === target) {
      targetNode = current;
    }
    if (current.left) {
      parent.set(current.left, current);
      q.push(current.left);
    }
    if (current.right) {
      parent.set(current.right, current);
      q.push(current.right);
    }
  }

  return targetNode;
}

function burnTree(start, parent) {
  const visited = new Set();
  const q = [start];
  visited.add(start);
  let time = 0;

  while (q.length > 0) {
    let flag = false; // did we add anything this round?
    const levelSize = q.length;
    for (let i = 0; i < levelSize; i++) {
      const current = q.shift();

      if (current.left && !visited.has(current.left)) {
        flag = true;
        q.push(current.left);
        visited.add(current.left);
      }
      if (current.right && !visited.has(current.right)) {
        flag = true;
        q.push(current.right);
        visited.add(current.right);
      }
      const par = parent.get(current);
      if (par && !visited.has(par)) {
        flag = true;
        q.push(par);
        visited.add(par);
      }
    }
    if (flag) time++;
  }

  return time;
}

function minTime(root, target) {
  const parent = new Map();
  const targetNode = buildParentMapping(root, parent, target);
  return burnTree(targetNode, parent);
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  root.left.right.left = new Node(7);
  root.right.right = new Node(6);
  return root;
}

console.log("Minimum time to burn the tree:", minTime(createSampleTree(), 5)); // 4
