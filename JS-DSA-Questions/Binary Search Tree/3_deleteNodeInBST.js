// Delete a node in a Binary Search Tree.

// Approach:
// 1. Leaf node (no children): remove it (return null).
// 2. One child: replace the node with its child.
// 3. Two children: find the inorder successor (smallest node in the right subtree), copy its value
//    into the node, then recursively delete the successor.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function deleteNodeInBST(root, key) {
  if (root === null) return root;

  if (root.data === key) {
    // Case 1: leaf node
    if (root.left === null && root.right === null) {
      return null;
    }
    // Case 2: one child
    else if (root.left === null) {
      return root.right;
    } else if (root.right === null) {
      return root.left;
    }
    // Case 3: two children
    else {
      let inorderSuccessor = root.right;
      while (inorderSuccessor.left !== null) {
        inorderSuccessor = inorderSuccessor.left;
      }
      root.data = inorderSuccessor.data;
      root.right = deleteNodeInBST(root.right, inorderSuccessor.data);
    }
  } else if (key > root.data) {
    root.right = deleteNodeInBST(root.right, key);
  } else {
    root.left = deleteNodeInBST(root.left, key);
  }

  return root;
}

function levelOrderTraversalLevelWise(root) {
  if (root === null) return;
  const q = [root, null];
  let line = [];
  while (q.length > 0) {
    const frontNode = q.shift();
    if (frontNode === null) {
      console.log(line.join(" "));
      line = [];
      if (q.length > 0) q.push(null);
    } else {
      line.push(frontNode.data);
      if (frontNode.left !== null) q.push(frontNode.left);
      if (frontNode.right !== null) q.push(frontNode.right);
    }
  }
}

function createSampleBST() {
  const root = new Node(50);
  root.left = new Node(30);
  root.right = new Node(70);
  root.left.left = new Node(20);
  root.left.left.left = new Node(10);
  root.left.right = new Node(40);
  root.right.right = new Node(80);
  return root;
}

let root = createSampleBST();
console.log("Level Wise Order before Deletion:");
levelOrderTraversalLevelWise(root);

const key = 30;
root = deleteNodeInBST(root, key);
console.log(`Level Wise Order after Deletion of ${key}:`);
levelOrderTraversalLevelWise(root);
