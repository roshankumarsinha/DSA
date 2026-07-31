// Find the middle of a linked list. If the number of nodes is odd, return the middle node.
// If even, return the SECOND middle node.

// Notes : https://takeuforward.org/data-structure/find-middle-element-in-a-linked-list/

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

// Two-pointer ("slow and fast") technique:
// 1. slow moves one node at a time; fast moves two nodes at a time.
// 2. When fast reaches the end, slow is at the middle.
// 3. For an even count, this returns the second middle node.
function findMiddle(head) {
  if (head === null) return null;

  let slow = head;
  let fast = head;

  while (fast !== null && fast.next !== null) {
    slow = slow.next;
    fast = fast.next.next;
  }

  return slow;
}

function printList(head) {
  const values = [];
  let temp = head;
  while (temp) {
    values.push(temp.data);
    temp = temp.next;
  }
  console.log(values.join(" "));
}

// Build 1 -> 2 -> 3 -> 4 -> 5
const head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);

process.stdout.write("Original List: ");
printList(head);

const middle = findMiddle(head);
console.log(middle !== null ? `Middle Node: ${middle.data}` : "The list is empty."); // 3
