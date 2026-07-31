// Zig-zag (spiral) level-order traversal of a binary tree.
// Level 1 left→right, level 2 right→left, level 3 left→right, etc.

// Example:
//        1
//       / \
//      2   3
//     / \    \
//    4   5    6
// Zig-Zag: 1 3 2 4 5 6

// Approach: level-order BFS with a queue and a leftToRight flag. For each level, place node values
// at the front or back of a deque depending on direction.
// Time O(N), Space O(N).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used a std::deque with push_front/push_back. A JS array supports unshift()
// (front) and push() (back), which we use to build each level in the right order.
function zigzagTraversal(root) {
  const result = [];
  if (root === null) return result;

  const q = [root];
  let leftToRight = true;

  while (q.length > 0) {
    const levelSize = q.length;
    const levelNodes = [];

    for (let i = 0; i < levelSize; i++) {
      const current = q.shift();
      if (leftToRight) {
        levelNodes.push(current.data);
      } else {
        levelNodes.unshift(current.data);
      }
      if (current.left) q.push(current.left);
      if (current.right) q.push(current.right);
    }

    result.push(...levelNodes);
    leftToRight = !leftToRight;
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

console.log(zigzagTraversal(createSampleTree()).join(" ")); // 1 3 2 4 5 6
