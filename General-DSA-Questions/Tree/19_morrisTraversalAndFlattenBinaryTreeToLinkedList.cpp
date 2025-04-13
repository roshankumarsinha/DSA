// Write a function to do Morris Traversal of a binary tree.
// Morris Traversal is an efficient in-place tree traversal technique that does not use recursion or extra space (like a stack or queue). It modifies the tree temporarily to establish threaded binary links for traversal.

// Why Morris Traversal?
//  1. ✅ No extra space (O(1) auxiliary space, unlike recursion or stack-based traversal).
//  2. ✅ Efficient O(N) time complexity.

// https://takeuforward.org/data-structure/morris-preorder-traversal-of-a-binary-tree/ -> Follow this link for pre-order Morris Traversal
// https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/ -> Follow this link for in-order Morris Traversal
// https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/ -> Follow this link for flattening a binary tree to a linked list

// Approach for Inorder Traversal Using Morris Traversal :-
//  Step 1: Initialize the current node as the root.
//  Step 2: If the current node has no left child:
//    a.  Print the current node.
//    b.  Move to the right child.
//  Step 3: If the current node has a left child:
//    a.  Find the rightmost node (inorder predecessor) of the left subtree.
//    b.  If the rightmost node’s right is NULL:
//      b1. Set its right to the current node (temporary thread).
//      b2. Move to the left child.
//    c.  If the rightmost node’s right is the current node:
//      c1. Restore the tree (remove the thread).
//      c2. Print the current node.
//      c3. Move to the right child.
//  Step 4: Repeat until all nodes are visited.
 
// Approach for Preorder Traversal Using Morris Traversal :- (Similar to inorder Morris traversal, but we print the node before moving to the left subtree.)
//  Step 1: If the node has no left child, print it and move to the right.
//  Step 2: If the node has a left child:
//    a.  Find its inorder predecessor.
//    b.  If the right pointer of the predecessor is NULL:
//      b1. Print the current node (before creating the thread).
//      b2. Make a thread to the current node.
//      b3. Move to the left.
//    c.  If the right pointer is already pointing to the current node:
//      c1. Remove the thread.
//      c2. Move to the right.