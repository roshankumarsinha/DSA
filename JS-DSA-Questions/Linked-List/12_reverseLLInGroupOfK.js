// Reverse a linked list in groups of size k.
// e.g. 1->2->3->4->5->6->7->8->9->10 with k=3 becomes 3->2->1->6->5->4->9->8->7->10.
// A final group with fewer than k nodes is left as-is.

// Notes : https://takeuforward.org/data-structure/reverse-linked-list-in-groups-of-size-k/

// Intuition (iterative): break the list into segments of k nodes and reverse each segment,
// stitching the reversed segments back together.

class Node {
  constructor(data, next = null) {
    this.data = data;
    this.next = next;
  }
}

// Reverse a whole linked list (3-pointer approach)
function reverseLinkedList(head) {
  let temp = head;
  let prev = null;
  while (temp !== null) {
    const front = temp.next;
    temp.next = prev;
    prev = temp;
    temp = front;
  }
  return prev;
}

// Get the k-th node from a starting position (or null if fewer than k remain)
function getKthNode(temp, k) {
  k -= 1; // we already start at the 1st node
  while (temp !== null && k > 0) {
    k--;
    temp = temp.next;
  }
  return temp;
}

function kReverse(head, k) {
  let temp = head;
  let prevLast = null; // last node of the previously reversed group

  while (temp !== null) {
    const kThNode = getKthNode(temp, k);

    // Incomplete group at the end → leave as-is
    if (kThNode === null) {
      if (prevLast) {
        prevLast.next = temp;
      }
      break;
    }

    const nextNode = kThNode.next; // remember where the next group starts
    kThNode.next = null; // cut the current group off before reversing

    const newHead = reverseLinkedList(temp); // reverse this group

    if (temp === head) {
      head = newHead; // first group becomes the new overall head
    } else {
      prevLast.next = newHead; // link previous group to this reversed group
    }

    prevLast = temp; // temp is now the tail of the reversed group
    temp = nextNode; // move to the next group
  }

  return head;
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

// Build 5 -> 4 -> 3 -> 7 -> 9 -> 2
let head = new Node(5);
head.next = new Node(4);
head.next.next = new Node(3);
head.next.next.next = new Node(7);
head.next.next.next.next = new Node(9);
head.next.next.next.next.next = new Node(2);

process.stdout.write("Original Linked List: ");
printLinkedList(head);

head = kReverse(head, 4);

process.stdout.write("Reversed Linked List: ");
printLinkedList(head);
