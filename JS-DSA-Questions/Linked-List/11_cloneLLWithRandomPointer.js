// Clone a linked list that has a next pointer AND a random pointer.
// The random pointer can point to any node in the list or be null.

// Notes : https://takeuforward.org/data-structure/clone-linked-list-with-random-and-next-pointer/

// Approach 1 (Map): map each original node to its clone, then wire up next/random. O(n) time, O(n) space.
// Approach 2 (used here, O(1) extra space):
//   Step 1: insert a clone of each node right after the original: 1 -> 1' -> 2 -> 2' -> ...
//   Step 2: set clone.random = original.random.next (the clone of the random target).
//   Step 3: detach the cloned list from the original, restoring the original's next pointers.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
    this.random = null;
  }
}

function copyRandomList(head) {
  if (!head) return null;

  // Step 1: interleave clones
  let current = head;
  while (current) {
    const newNode = new Node(current.data);
    newNode.next = current.next;
    current.next = newNode;
    current = newNode.next; // move to the next original node
  }

  // Step 2: assign random pointers of clones
  current = head;
  while (current) {
    if (current.random) {
      // current.next is the clone of current; its random is the clone of current.random
      current.next.random = current.random.next;
    }
    current = current.next.next;
  }

  // Step 3: separate the two lists
  const newHead = head.next;
  let original = head;
  let clone = newHead;
  while (original) {
    original.next = original.next.next;
    if (clone.next) {
      clone.next = clone.next.next;
    }
    original = original.next;
    clone = clone.next;
  }

  return newHead;
}

function printList(head) {
  let temp = head;
  while (temp) {
    const rand = temp.random ? temp.random.data : "NULL";
    console.log(`Node: ${temp.data}, Random: ${rand}`);
    temp = temp.next;
  }
  console.log();
}

function insertNode(head, data) {
  const newNode = new Node(data);
  if (!head) return newNode;
  let temp = head;
  while (temp.next) temp = temp.next;
  temp.next = newNode;
  return head;
}

// Build 1 -> 2 -> 3 -> 4
let head = null;
head = insertNode(head, 1);
head = insertNode(head, 2);
head = insertNode(head, 3);
head = insertNode(head, 4);

// Assign random pointers
head.random = head.next.next; // 1 -> 3
head.next.random = head; // 2 -> 1
head.next.next.random = head.next.next; // 3 -> itself
head.next.next.next.random = head.next; // 4 -> 2

console.log("Original List:");
printList(head);

const copiedList = copyRandomList(head);
console.log("Copied List:");
printList(copiedList);
