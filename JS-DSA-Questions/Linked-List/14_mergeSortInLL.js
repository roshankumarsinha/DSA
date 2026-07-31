// Perform merge sort on a linked list.

// Notes : https://takeuforward.org/linked-list/sort-a-linked-list

// Approach (same as array merge sort):
// 1. Find the middle using slow/fast pointers.
// 2. Split into two halves and recursively sort each.
// 3. Merge the two sorted halves.

class Node {
  constructor(data, next = null) {
    this.data = data;
    this.next = next;
  }
}

function mergeTwoSortedLinkedLists(list1, list2) {
  const dummyNode = new Node(-1);
  let temp = dummyNode;

  while (list1 !== null && list2 !== null) {
    if (list1.data <= list2.data) {
      temp.next = list1;
      list1 = list1.next;
    } else {
      temp.next = list2;
      list2 = list2.next;
    }
    temp = temp.next;
  }

  temp.next = list1 !== null ? list1 : list2;
  return dummyNode.next;
}

// Find the middle. Note fast starts at head.next so that, for an even count, `middle` ends up at
// the end of the FIRST half — this is important for splitting into two non-empty halves.
function findMiddle(head) {
  if (head === null || head.next === null) {
    return head;
  }

  let slow = head;
  let fast = head.next;

  while (fast !== null && fast.next !== null) {
    slow = slow.next;
    fast = fast.next.next;
  }

  return slow;
}

function sortLL(head) {
  // Base case: 0 or 1 node is already sorted
  if (head === null || head.next === null) {
    return head;
  }

  const middle = findMiddle(head);

  // Split into two halves
  const right = middle.next;
  middle.next = null; // break the list
  let left = head;

  left = sortLL(left);
  const sortedRight = sortLL(right);

  return mergeTwoSortedLinkedLists(left, sortedRight);
}

function printLinkedList(head) {
  const values = [];
  let temp = head;
  while (temp !== null) {
    values.push(temp.data);
    temp = temp.next;
  }
  console.log(values.join(" "));
}

// Build 3 -> 2 -> 5 -> 4 -> 1
let head = new Node(3);
head.next = new Node(2);
head.next.next = new Node(5);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(1);

process.stdout.write("Original Linked List: ");
printLinkedList(head);

head = sortLL(head);

process.stdout.write("Sorted Linked List: ");
printLinkedList(head); // 1 2 3 4 5
