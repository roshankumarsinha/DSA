// Check if a binary tree is a max-heap.

// A max-heap must satisfy:
// 1. Complete Binary Tree (CBT): all levels full except possibly the last, filled left to right.
// 2. Heap Order: every node >= its children.

// Approach: level-order traversal. Once a missing child is seen, no later node may have a child.
// Simultaneously check the heap-order property. O(N) time and space.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used std::queue. Here a plain array is the queue (push()/shift()).
function isMaxHeap(root) {
  if (root === null) return true;

  const q = [root];
  let nullChildSeen = false;

  while (q.length > 0) {
    const current = q.shift();

    // Left child
    if (current.left) {
      if (nullChildSeen || current.data < current.left.data) return false;
      q.push(current.left);
    } else {
      nullChildSeen = true;
    }

    // Right child
    if (current.right) {
      if (nullChildSeen || current.data < current.right.data) return false;
      q.push(current.right);
    } else {
      nullChildSeen = true;
    }
  }

  return true;
}

// Driver code
const root = new Node(10);
root.left = new Node(9);
root.right = new Node(8);
root.left.left = new Node(7);
// root.right.left = new Node(6); // uncomment to break the max-heap property

console.log(isMaxHeap(root) ? "The binary tree is a max-heap." : "The binary tree is not a max-heap.");
