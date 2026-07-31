// Remove duplicates from a SORTED linked list, modifying it in place; return the head.

// Intuition:
// 1. The list is sorted, so duplicates are adjacent.
// 2. If current.data === current.next.data, skip the next node.
// 3. Otherwise move to the next node. Continue to the end.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

function removeDuplicates(head) {
  if (head === null || head.next === null) return head;

  let current = head;

  while (current !== null && current.next !== null) {
    if (current.data === current.next.data) {
      // Skip the duplicate node (JS is garbage-collected, so there is no manual `delete`)
      current.next = current.next.next;
    } else {
      current = current.next;
    }
  }

  return head;
}

function printList(head) {
  const values = [];
  let current = head;
  while (current !== null) {
    values.push(current.data);
    current = current.next;
  }
  console.log(values.join(" "));
}

// Build 1 -> 2 -> 2 -> 2 -> 3
const head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(2);
head.next.next.next = new Node(2);
head.next.next.next.next = new Node(3);

printList(head); // 1 2 2 2 3
printList(removeDuplicates(head)); // 1 2 3

// If the list were NOT sorted, two options:
// 1. Hashing (Set): O(N) time, O(N) space — track seen values and unlink repeats.
// 2. Two pointers: O(N^2) time, O(1) space — brute force.
