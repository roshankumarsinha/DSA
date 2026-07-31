// Construct a unique binary tree from its preorder and inorder traversals.

// Example:
// Inorder:  [40, 20, 50, 10, 60, 30]
// Preorder: [10, 20, 40, 50, 30, 60]
//         10
//       /    \
//      20     30
//     / \      \
//    40  50    60

// Video link : https://www.youtube.com/watch?v=aZNaLrVebKQ
// Notes link : https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/

// Approach:
// 1. The first element of preorder is the root.
// 2. Locate the root in inorder (use a value→index map for O(1) lookups).
// 3. Elements left of it in inorder form the left subtree; right of it, the right subtree.
// 4. Recurse using index windows [inStart..inEnd] and [preStart..preEnd].

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

// JavaScript note: C++ used unordered_map<int,int> for value→index. Here we use a Map.
function buildTreeHelper(inorder, preorder, inStart, inEnd, preStart, preEnd, inIndexMap) {
  if (inStart > inEnd || preStart > preEnd) return null;

  const rootValue = preorder[preStart];
  const root = new Node(rootValue);

  const rootIndex = inIndexMap.get(rootValue);
  const leftSize = rootIndex - inStart;

  // Left subtree
  root.left = buildTreeHelper(
    inorder,
    preorder,
    inStart,
    rootIndex - 1,
    preStart + 1,
    preStart + leftSize,
    inIndexMap
  );

  // Right subtree
  root.right = buildTreeHelper(
    inorder,
    preorder,
    rootIndex + 1,
    inEnd,
    preStart + leftSize + 1,
    preEnd,
    inIndexMap
  );

  return root;
}

function buildTree(inorder, preorder) {
  const inIndexMap = new Map();
  for (let i = 0; i < inorder.length; i++) {
    inIndexMap.set(inorder[i], i);
  }
  return buildTreeHelper(inorder, preorder, 0, inorder.length - 1, 0, preorder.length - 1, inIndexMap);
}

function printInOrder(root, out = []) {
  if (!root) return out;
  printInOrder(root.left, out);
  out.push(root.data);
  printInOrder(root.right, out);
  return out;
}

const inorder = [40, 20, 50, 10, 60, 30];
const preorder = [10, 20, 40, 50, 30, 60];
const root = buildTree(inorder, preorder);
console.log("Inorder traversal of the constructed tree:", printInOrder(root).join(" ")); // 40 20 50 10 60 30
