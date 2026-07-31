// Reverse a linked list.

// Notes (Check Optimal Approach 1) : https://takeuforward.org/data-structure/reverse-a-linked-list/

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

// prevNode: the previous node (initially null).
// currentNode: the current node (initially head).
// nextNode: temporarily holds the next node while reversing the link.
function reverseLinkedList(head) {
  let prevNode = null;
  let currentNode = head;
  let nextNode = null;

  while (currentNode !== null) {
    nextNode = currentNode.next; // store next node
    currentNode.next = prevNode; // reverse current node's pointer
    prevNode = currentNode; // move pointers one step ahead
    currentNode = nextNode;
  }

  return prevNode; // new head
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
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);

process.stdout.write("Original List: ");
printList(head);

head = reverseLinkedList(head);

process.stdout.write("Reversed List: ");
printList(head);
