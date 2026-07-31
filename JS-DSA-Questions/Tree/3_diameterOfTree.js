// Find the diameter of a binary tree.
// Diameter = number of nodes on the longest path between two leaves (this file counts nodes; for
// an edge count, drop the +1).

// Approach 1 (naive): for each node, diameter = max(leftDiameter, rightDiameter, leftH + rightH + 1),
// where heights are recomputed each time → O(N^2).

// Approach 2 (optimized): a single DFS that returns both height and diameter for each subtree, so
// heights are computed once → O(N) time, O(N) space.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ returned pair<int,int> {height, diameter}. Here we return an object
// { height, diameter }.
function diameterOfTree(root) {
  if (root === null) {
    return { height: 0, diameter: 0 };
  }

  const leftPair = diameterOfTree(root.left);
  const rightPair = diameterOfTree(root.right);

  const opt1 = leftPair.diameter;
  const opt2 = rightPair.diameter;
  const opt3 = leftPair.height + rightPair.height + 1; // path through this node (nodes counted)

  const height = Math.max(leftPair.height, rightPair.height) + 1;
  const diameter = Math.max(opt1, opt2, opt3);

  return { height, diameter };
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.right = new Node(5);
  root.right.left = new Node(6);
  root.right.right = new Node(7);
  return root;
}

const root = createSampleTree();
console.log("Diameter of the Tree (Optimized):", diameterOfTree(root).diameter); // 4 (as edges) / here nodes-path max
