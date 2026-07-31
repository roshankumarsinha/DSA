// Implement a Singly Linked List

// Notes for Theory of Linked List: https://takeuforward.org/linked-list/linked-list-introduction

// JavaScript note: C++ passed the head/tail as `Node* &` (a reference to a pointer) so a function
// could reassign the caller's head. JavaScript has no pass-by-reference for variables, so functions
// that may change the head RETURN the new head, and the caller reassigns it. We return an object
// { head, tail } where both can change. `null` replaces C++ `nullptr`.
class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

function insertAtBegining(data, head) {
  const temp = new Node(data);
  temp.next = head;
  return temp; // new head
}

function insertAtEnd(data, tail) {
  const temp = new Node(data);
  tail.next = temp;
  return temp; // new tail
}

// Intuition:
// 1. If position is 1, insert at the beginning.
// 2. If position is greater than the length of the list, insert at the end.
// Returns { head, tail } since either may change.
function insertAtMiddle(data, position, head, tail) {
  if (position <= 0) {
    console.log("You entered wrong position value");
    return { head, tail };
  }
  const temp = new Node(data);
  let temp1 = head;
  let count = 1;
  if (position === count) {
    temp.next = head;
    return { head: temp, tail };
  }

  // Traverse to the node just before the insert position
  while (count !== position - 1 && temp1 !== null) {
    temp1 = temp1.next;
    count++;
  }
  if (temp1 === null) {
    console.log("Position you mentioned is too large");
    return { head, tail };
  } else if (temp1 === tail) {
    temp1.next = temp;
    return { head, tail: temp };
  } else {
    temp.next = temp1.next; // link new node to the next node
    temp1.next = temp; // link temp1 to new node
    return { head, tail };
  }
}

function deleteAtBegining(head) {
  if (head === null) {
    console.log("List is already Empty");
    return null;
  }
  if (head.next === null) {
    return null;
  }
  const temp = head.next;
  head.next = null;
  return temp; // new head
}

function printList(head) {
  if (head === null) {
    console.log("No data to print");
    return;
  }
  const values = [];
  let temp = head;
  while (temp !== null) {
    values.push(temp.data);
    temp = temp.next;
  }
  console.log("Data :", values.join(" "));
}

// Driver code
let head = new Node(10);
let tail = head;
console.log("Head :", head.data);
console.log("Tail :", tail.data);

head = insertAtBegining(12, head);
printList(head);
head = insertAtBegining(15, head);
printList(head);
tail = insertAtEnd(16, tail);
printList(head);
({ head, tail } = insertAtMiddle(11, 2, head, tail));
printList(head);
head = deleteAtBegining(head);
printList(head);
