// Find the starting node of a loop in a linked list (and thereby remove/identify it).

// Notes : https://takeuforward.org/data-structure/starting-point-of-loop-in-a-linked-list/

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

// Detect a cycle; return the meeting point (or null if no cycle) using Floyd's algorithm.
function detectCycle(head) {
  if (head === null) return null;

  let slow = head;
  let fast = head;

  while (fast !== null && fast.next !== null) {
    slow = slow.next;
    fast = fast.next.next;
    if (slow === fast) {
      return slow;
    }
  }

  return null;
}

// Find the start of the cycle: reset one pointer to head, then move both one step at a time.
function removeCycle(head) {
  let meetingPoint = detectCycle(head);
  if (meetingPoint === null) return null;

  let slow = head;
  while (slow !== meetingPoint) {
    slow = slow.next;
    meetingPoint = meetingPoint.next;
  }

  return slow; // start of the cycle
}

// Helper to create a cycle for testing. pos = 0-indexed start of the cycle; -1 = no cycle.
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

  temp.next = cycleNode;
}

// Build 1 -> 2 -> 3 -> 4 -> 5
const head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);
createCycle(head, 2);

const cycleStart = removeCycle(head);
console.log(cycleStart ? `Cycle starts at node: ${cycleStart.data}` : "No cycle detected");

// Math behind why slow (reset to head) and the meeting point converge at the cycle start:
// Let x = distance from head to cycle start, y = distance from cycle start to meeting point,
// C = cycle length. Slow travels x + y before meeting; fast travels 2(x + y) = x + y + kC.
// So x + y = kC, meaning x is a multiple of C minus y. Moving both one step at a time, they
// meet exactly at the cycle start after x steps.
