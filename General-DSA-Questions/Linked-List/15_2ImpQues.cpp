// Question 1 : Find intersection of Two Linked Lists
// Problem Statement: Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect.
// If the two linked lists have no intersection at all, return null.

// Intiution:
// 1. Calculate the lengths of both linked lists. Say the lengths are lenA and lenB.
// 2. Find the difference in lengths, say d = |lenA - lenB|.
// 3. Move the pointer of the longer list d nodes ahead.
// 4. Now, move both pointers one node at a time until they meet. The meeting point is the intersection node.
// 5. If they reach the end (nullptr) without meeting, then there is no intersection.



// Question 2 : Rotate a Linked List
// Problem Statement: Given the head of a linked list, rotate the list to the right by k places and return the new head of the rotated list.

// Intiution:
// 1. Calculate the length of the linked list, say len.
// 2. If k >= len, then do k = k % len to handle cases where k is greater than the length of the list.
// 3. If k is 0 after the above step, return the head as no rotation is needed.
// 4. Find the (len - k)th node in the list. This will be the new tail after rotation.
// 5. The next node of the new tail will be the new head.
// 6. Set the next of the current tail to the current head to make it circular.
// 7. Set the next of the new tail to nullptr to break the circularity.
// 8. Return the new head.
