// Create a Binary Search Tree (BST) and traverse it level by level.

// Insert approach:
// 1. If root is null, create and return a new node.
// 2. If data > root.data, insert into the right subtree.
// 3. If data < root.data, insert into the left subtree.
// 4. Return the root.
// Time: O(log N) average, O(N) worst. Space: O(log N) average, O(N) worst.

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function insertIntoBST(root, data) {
  if (root === null) {
    return new Node(data);
  }

  if (data > root.data) {
    root.right = insertIntoBST(root.right, data);
  } else {
    root.left = insertIntoBST(root.left, data);
  }

  return root;
}

// C++ read values from cin until -1. Here we build the BST from an array (terminated by -1).
function createBST(values) {
  let root = null;
  for (const data of values) {
    if (data === -1) break;
    root = insertIntoBST(root, data);
  }
  return root;
}

// Level-order traversal, printing each level on its own line.
// JavaScript note: C++ used std::queue and pushed NULL as a level separator; here we use a plain
// array as a queue and the same NULL(-marker) trick with null.
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

// Search a value in a BST (recursive)
function searchInBST(root, data) {
  if (root === null || root.data === data) return root;
  return data > root.data ? searchInBST(root.right, data) : searchInBST(root.left, data);
}

// Driver code — input: 50 30 40 20 60 55 70 80 25 -1
const root = createBST([50, 30, 40, 20, 60, 55, 70, 80, 25, -1]);
console.log("Level Wise Order:");
levelOrderTraversalLevelWise(root);
/*
50
30 60
20 40 55 70
25 80
*/
