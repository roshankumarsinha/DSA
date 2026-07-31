// Check if a linked list is a palindrome (reads the same forwards and backwards).

// Notes : https://takeuforward.org/data-structure/check-if-given-linked-list-is-plaindrome/

// Approach 1: copy values into an array and check the array (O(n) extra space).
// Approach 2 (used here): reverse the second half and compare with the first half (O(1) space).

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

function isPalindrome(head) {
  if (head === null || head.next === null) return true;

  // Find the middle with slow/fast pointers
  let slow = head;
  let fast = head;
  while (fast !== null && fast.next !== null) {
    slow = slow.next;
    fast = fast.next.next;
  }

  // Reverse the second half (from slow)
  let secondHalf = reverseList(slow);

  // Compare the first half with the reversed second half
  let firstHalf = head;
  while (secondHalf !== null) {
    if (firstHalf.data !== secondHalf.data) {
      return false;
    }
    firstHalf = firstHalf.next;
    secondHalf = secondHalf.next;
  }

  return true;
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

// Build 1 -> 2 -> 3 -> 2 -> 1
const head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(2);
head.next.next.next.next = new Node(1);

process.stdout.write("Linked List: ");
printList(head);

console.log(isPalindrome(head) ? "The linked list is a palindrome." : "The linked list is not a palindrome.");
