// Merge two sorted linked lists into a single sorted linked list; return the head.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

function mergeSortedLists(l1, l2) {
  if (l1 === null) return l2;
  if (l2 === null) return l1;

  // Dummy node simplifies building the merged list
  const dummy = new Node(-1);
  let current = dummy;

  while (l1 !== null && l2 !== null) {
    if (l1.data <= l2.data) {
      current.next = l1; // append l1's node
      l1 = l1.next;
    } else {
      current.next = l2; // append l2's node
      l2 = l2.next;
    }
    current = current.next;
  }

  // Append remaining nodes
  current.next = l1 !== null ? l1 : l2;

  return dummy.next;
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

// List 1: 1 -> 3 -> 5
const l1 = new Node(1);
l1.next = new Node(3);
l1.next.next = new Node(5);

// List 2: 2 -> 4 -> 6
const l2 = new Node(2);
l2.next = new Node(4);
l2.next.next = new Node(6);

process.stdout.write("List 1: ");
printList(l1);
process.stdout.write("List 2: ");
printList(l2);

const mergedList = mergeSortedLists(l1, l2);
process.stdout.write("Merged List: ");
printList(mergedList); // 1 2 3 4 5 6
