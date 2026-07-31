// Two important linked-list problems (theory + reference implementations).

// =====================================================================================
// Question 1 : Find the intersection of two linked lists
// =====================================================================================
// Given the heads of two singly linked lists headA and headB, return the node at which they
// intersect, or null if they never intersect.
//
// Intuition:
// 1. Compute lengths lenA and lenB.
// 2. d = |lenA - lenB|. Advance the longer list's pointer d nodes.
// 3. Move both pointers together until they meet — that node is the intersection.
// 4. If they reach the end (null) without meeting, there is no intersection.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

function getLength(head) {
  let len = 0;
  while (head !== null) {
    len++;
    head = head.next;
  }
  return len;
}

function getIntersectionNode(headA, headB) {
  let lenA = getLength(headA);
  let lenB = getLength(headB);

  let a = headA;
  let b = headB;

  // Advance the longer list's pointer by the length difference
  while (lenA > lenB) {
    a = a.next;
    lenA--;
  }
  while (lenB > lenA) {
    b = b.next;
    lenB--;
  }

  // Move together until they meet (or both reach null)
  while (a !== b) {
    a = a.next;
    b = b.next;
  }
  return a; // intersection node or null
}

// =====================================================================================
// Question 2 : Rotate a linked list to the right by k places
// =====================================================================================
// Intuition:
// 1. Compute length len.
// 2. k = k % len (handles k >= len). If k === 0, no rotation needed.
// 3. The new tail is the (len - k)th node; the node after it becomes the new head.
// 4. Make the list circular (old tail -> old head), then break it at the new tail.

function rotateRight(head, k) {
  if (head === null || head.next === null || k === 0) return head;

  // Compute length and find the current tail
  let len = 1;
  let tail = head;
  while (tail.next !== null) {
    tail = tail.next;
    len++;
  }

  k = k % len;
  if (k === 0) return head;

  // Make the list circular
  tail.next = head;

  // New tail is at position (len - k); new head is the node after it
  let stepsToNewTail = len - k;
  let newTail = head;
  for (let i = 1; i < stepsToNewTail; i++) {
    newTail = newTail.next;
  }
  const newHead = newTail.next;
  newTail.next = null; // break the circle

  return newHead;
}

// Demo for rotation: 1 -> 2 -> 3 -> 4 -> 5, k = 2  →  4 -> 5 -> 1 -> 2 -> 3
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);

let rotated = rotateRight(head, 2);
const out = [];
while (rotated) {
  out.push(rotated.data);
  rotated = rotated.next;
}
console.log(out.join(" ")); // 4 5 1 2 3
