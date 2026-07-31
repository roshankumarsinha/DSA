// Sort a linked list containing only 0s, 1s, and 2s. Data replacement is NOT allowed (we must
// relink the actual nodes).

// Approach 1 (not recommended): count 0s, 1s, 2s, then overwrite node data.
// Approach 2 (used here): create three separate lists for 0s, 1s, 2s, then join them.

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

function sortList(head) {
  // Dummy heads for the three lists make insertion easier
  const zeroHead = new Node(-1);
  const oneHead = new Node(-1);
  const twoHead = new Node(-1);

  let zeroTail = zeroHead;
  let oneTail = oneHead;
  let twoTail = twoHead;

  let current = head;

  while (current !== null) {
    const val = current.data;
    if (val === 0) {
      zeroTail.next = current;
      zeroTail = zeroTail.next;
    } else if (val === 1) {
      oneTail.next = current;
      oneTail = oneTail.next;
    } else {
      twoTail.next = current;
      twoTail = twoTail.next;
    }
    current = current.next;
  }

  // Join the three lists: zeros -> ones -> twos
  zeroTail.next = oneHead.next !== null ? oneHead.next : twoHead.next;
  oneTail.next = twoHead.next;
  twoTail.next = null;

  return zeroHead.next;
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

// Build 1 -> 2 -> 0 -> 1 -> 2 -> 0
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(0);
head.next.next.next = new Node(1);
head.next.next.next.next = new Node(2);
head.next.next.next.next.next = new Node(0);

process.stdout.write("Original List: ");
printList(head);

head = sortList(head);

process.stdout.write("Sorted List: ");
printList(head); // 0 0 1 1 2 2
