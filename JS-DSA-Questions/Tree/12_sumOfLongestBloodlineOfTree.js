// Sum of the longest bloodline (longest root-to-leaf path) of a tree.
// If multiple paths share the maximum length, choose the one with the maximum sum.

// Example:
//        1
//       / \
//      2   3
//     /     \
//    4       5
//   /         \
//  7           8
// Paths: 1->2->4->7 (14), 1->3->5->8 (17) → answer 17.

// Approach (DFS): track the current depth and path sum. On reaching a leaf (null child boundary),
// update (maxLength, maxSum): a strictly longer path replaces; an equally long path takes the max sum.
// Time O(N), Space O(H).

class Node {
  constructor(val) {
    this.data = val;
    this.left = null;
    this.right = null;
  }
}

function sumOfLongestBloodline(root) {
  // JavaScript note: C++ passed maxLength & maxSum by reference (int&). Here we keep them in a
  // shared state object that the recursion mutates.
  const state = { maxLength: 0, maxSum: 0 };

  function dfs(node, depth, sum) {
    if (node === null) {
      if (depth > state.maxLength) {
        state.maxLength = depth;
        state.maxSum = sum;
      } else if (depth === state.maxLength) {
        state.maxSum = Math.max(state.maxSum, sum);
      }
      return;
    }

    sum += node.data;
    dfs(node.left, depth + 1, sum);
    dfs(node.right, depth + 1, sum);
  }

  dfs(root, 0, 0);
  return state.maxSum;
}

function createSampleTree() {
  const root = new Node(1);
  root.left = new Node(2);
  root.right = new Node(3);
  root.left.left = new Node(4);
  root.left.left.left = new Node(7);
  root.right.right = new Node(5);
  root.right.right.right = new Node(8);
  return root;
}

console.log("Sum of the longest bloodline of the tree:", sumOfLongestBloodline(createSampleTree())); // 17
