// Add two numbers represented by linked lists (each node holds one digit).

// Notes : https://takeuforward.org/data-structure/add-two-numbers-represented-as-linked-lists/

// Approach:
// 1. Reverse both lists so the least significant digit is at the head.
// 2. Traverse both, adding corresponding digits plus carry, building a result list.
// 3. Reverse the result list to restore normal order.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

function reverseList(head) {
  let prev = null;
  let curr = head;
  let next = null;
  while (curr !== null) {
    next = curr.next;
    curr.next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

function addTwoNumbers(l1, l2) {
  l1 = reverseList(l1);
  l2 = reverseList(l2);

  let result = null;
  let current = null;
  let carry = 0;

  // Single combined loop (equivalent to the three separate C++ loops):
  // continue while either list has nodes or there is a leftover carry.
  while (l1 !== null || l2 !== null || carry > 0) {
    const sum = (l1 ? l1.data : 0) + (l2 ? l2.data : 0) + carry;
    carry = Math.floor(sum / 10);
    const digit = sum % 10;

    const newNode = new Node(digit);
    if (result === null) {
      result = newNode;
      current = result;
    } else {
      current.next = newNode;
      current = current.next;
    }

    if (l1) l1 = l1.next;
    if (l2) l2 = l2.next;
  }

  return reverseList(result);
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

// List 1: 2 -> 4 -> 3 (represents 342)
const l1 = new Node(2);
l1.next = new Node(4);
l1.next.next = new Node(3);

// List 2: 5 -> 6 -> 4 (represents 465)
const l2 = new Node(5);
l2.next = new Node(6);
l2.next.next = new Node(4);

process.stdout.write("List 1: ");
printList(l1);
process.stdout.write("List 2: ");
printList(l2);

const result = addTwoNumbers(l1, l2);
process.stdout.write("Result: ");
printList(result); // 8 0 7  (342 + 465 = 807)
