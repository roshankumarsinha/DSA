// Detect a loop in a linked list. Return true if a loop is detected, otherwise false.

// Notes : https://takeuforward.org/data-structure/detect-a-cycle-in-a-linked-list/

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

// Floyd's Cycle-Finding Algorithm ("Tortoise and Hare"):
// 1. slow moves one step; fast moves two steps.
// 2. If there is a cycle, they eventually meet inside it.
// 3. If fast reaches the end (null), there is no cycle.
// The gap between them shrinks by 1 each step, so they must meet if a cycle exists.
function hasCycle(head) {
  if (head === null) return false;

  let slow = head;
  let fast = head;

  while (fast !== null && fast.next !== null) {
    slow = slow.next;
    fast = fast.next.next;

    if (slow === fast) {
      return true;
    }
  }

  return false;
}

// Helper to create a cycle for testing. pos = index where the cycle starts (0-indexed);
// pos = -1 means no cycle.
function createCycle(head, pos) {
  if (pos === -1) return;

  let temp = head;
  let cycleNode = null;
  let index = 0;

  while (temp.next !== null) {
    if (index === pos) {
      cycleNode = temp;
    }
    temp = temp.next;
    index++;
  }

  temp.next = cycleNode; // link last node to the cycle start
}

// Build 1 -> 2 -> 3 -> 4 -> 5
const head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);

createCycle(head, 2); // cycle back to index 2

console.log(hasCycle(head) ? "Cycle detected in the linked list." : "No cycle in the linked list.");
