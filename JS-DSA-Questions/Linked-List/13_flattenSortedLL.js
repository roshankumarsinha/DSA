// Flatten a multilevel sorted linked list.

// Notes : https://takeuforward.org/data-structure/flattening-a-linked-list/

// Each node has:
//   next  → next node horizontally
//   child → a sorted linked list vertically
// Flatten everything into a single sorted list linked via the `child` pointer.

// Approach (recursion, no extra space):
// 1. Reuse the "merge two sorted lists" idea, merging along the `child` pointer.
// 2. Recursively flatten from the rightmost list back to the head, merging pairs.

class Node {
  constructor(data = 0, next = null, child = null) {
    this.data = data;
    this.next = next;
    this.child = child;
  }
}

// Merge two vertically-linked (via `child`) sorted lists.
function merge(list1, list2) {
  const dummyNode = new Node(-1);
  let res = dummyNode;

  while (list1 !== null && list2 !== null) {
    if (list1.data < list2.data) {
      res.child = list1;
      res = list1;
      list1 = list1.child;
    } else {
      res.child = list2;
      res = list2;
      list2 = list2.child;
    }
    res.next = null; // keep the flattened list vertical
  }

  res.child = list1 !== null ? list1 : list2;

  if (dummyNode.child) {
    dummyNode.child.next = null;
  }

  return dummyNode.child;
}

function flattenLinkedList(head) {
  if (head === null || head.next === null) {
    return head;
  }

  // Flatten the rest first, then merge the current list into it
  const mergedHead = flattenLinkedList(head.next);
  head = merge(head, mergedHead);
  return head;
}

// Print by traversing the `child` pointers (the flattened direction)
function printLinkedList(head) {
  const values = [];
  while (head !== null) {
    values.push(head.data);
    head = head.child;
  }
  console.log(values.join(" "));
}

// Build the multilevel list
const head = new Node(5);
head.child = new Node(14);

head.next = new Node(10);
head.next.child = new Node(4);

head.next.next = new Node(12);
head.next.next.child = new Node(20);
head.next.next.child.child = new Node(13);

head.next.next.next = new Node(7);
head.next.next.next.child = new Node(17);

const flattened = flattenLinkedList(head);
process.stdout.write("Flattened linked list: ");
printLinkedList(flattened);
