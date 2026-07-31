// Doubly Linked List — theory notes and the "Design Browser History" problem.

// Notes:
// 1. https://takeuforward.org/linked-list/introduction-to-doubly-linked-list
// 2. Inserting into DLL : https://takeuforward.org/data-structure/insert-at-end-of-doubly-linked-list/
// 3. Deleting from DLL : https://takeuforward.org/data-structure/delete-last-node-of-a-doubly-linked-list/

// Question : Design Browser History
// You start on a homepage. You can visit a new URL, go back some steps, or go forward some steps.
// (Video: https://www.youtube.com/watch?v=mG3KLugbOdc)

// Intuition:
// 1. A doubly linked list fits naturally: we can move forward and backward and add pages.
// 2. Each node holds a URL.
// 3. A `current` pointer tracks the active page.
// 4. Visiting a new URL from the middle of history discards all forward history.

class Node {
  constructor(url) {
    this.url = url;
    this.prev = null;
    this.next = null;
  }
}

class BrowserHistory {
  constructor(homepage) {
    this.head = new Node(homepage);
    this.current = this.head;
  }

  // Visit a new URL. This drops any forward history (current.next is overwritten).
  visit(url) {
    const newNode = new Node(url);
    this.current.next = newNode;
    newNode.prev = this.current;
    this.current = newNode;
  }

  // Go back up to `steps` pages (not past the start)
  back(steps) {
    while (steps > 0 && this.current.prev !== null) {
      this.current = this.current.prev;
      steps--;
    }
    return this.current.url;
  }

  // Go forward up to `steps` pages (not past the end)
  forward(steps) {
    while (steps > 0 && this.current.next !== null) {
      this.current = this.current.next;
      steps--;
    }
    return this.current.url;
  }
}

// Driver code
const browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");
browserHistory.visit("facebook.com");
browserHistory.visit("youtube.com");
console.log(browserHistory.back(1)); // facebook.com
console.log(browserHistory.back(1)); // google.com
console.log(browserHistory.forward(1)); // facebook.com
browserHistory.visit("linkedin.com"); // drops forward history after facebook.com
console.log(browserHistory.forward(2)); // linkedin.com
console.log(browserHistory.back(2)); // google.com
console.log(browserHistory.back(7)); // leetcode.com
