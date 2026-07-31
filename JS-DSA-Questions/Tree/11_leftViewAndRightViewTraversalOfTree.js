// Left View and Right View of a binary tree.
// Left View: the first node visible from the left at each level.
// Right View: the last node at each level.

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
// Left View:  1 2 4
// Right View: 1 3 6

// Approach: level-order BFS. For Left View, take the first node of each level; for Right View, the
// last node of each level. Time O(N), Space O(N).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function leftView(root) {
  const result = [];
  if (root === null) return result;

  const q = [root];
  while (q.length > 0) {
    const levelSize = q.length;
    for (let i = 0; i < levelSize; i++) {
      const current = q.shift();
      if (i === 0) result.push(current.data); // first node of the level
      if (current.left) q.push(current.left);
      if (current.right) q.push(current.right);
    }
  }
  return result;
}

function rightView(root) {
  const result = [];
  if (root === null) return result;

  const q = [root];
  while (q.length > 0) {
    const levelSize = q.length;
    for (let i = 0; i < levelSize; i++) {
      const current = q.shift();
      if (i === levelSize - 1) result.push(current.data); // last node of the level
      if (current.left) q.push(current.left);
      if (current.right) q.push(current.right);
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

const root = createSampleTree();
console.log("Left View Traversal:", leftView(root).join(" ")); // 1 2 4
console.log("Right View Traversal:", rightView(root).join(" ")); // 1 3 6
