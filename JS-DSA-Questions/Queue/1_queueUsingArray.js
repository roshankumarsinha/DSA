// Implement a Queue class using an array with:
// enqueue(value) - adds an element to the end
// dequeue()      - removes and logs the front element; logs "Queue Underflow!" if empty
// isEmpty()      - returns true if the queue is empty
// displayFront() - logs the front element; logs "Queue is empty!" if empty

// JavaScript note: this mirrors the C++ fixed-size-array implementation with front/rear indices
// (rather than using JS array push/shift) so the mechanics of a queue are explicit. SIZE is the
// fixed capacity.
const SIZE = 5;

class Queue {
  constructor() {
    this.arr = new Array(SIZE);
    this.front = -1;
    this.rear = -1;
  }

  // Add element to the queue
  enqueue(value) {
    if (this.rear === SIZE - 1) {
      console.log("Queue Overflow!");
      return;
    }
    if (this.front === -1) this.front = 0; // first element
    this.rear = this.rear + 1;
    this.arr[this.rear] = value;
  }

  // Remove element from the queue
  dequeue() {
    if (this.front === -1 || this.front > this.rear) {
      console.log("Queue Underflow!");
      return;
    }
    console.log("Dequeued:", this.arr[this.front]);
    if (this.front === this.rear) {
      this.front = this.rear = -1; // last element
    } else {
      this.front = this.front + 1;
    }
  }

  // Display front element
  displayFront() {
    if (this.front === -1 || this.front > this.rear) {
      console.log("Queue is empty!");
    } else {
      console.log("Front:", this.arr[this.front]);
    }
  }

  // Check if the queue is empty
  isEmpty() {
    return this.front === -1 || this.front > this.rear;
  }
}

// Driver code
const q = new Queue();
q.enqueue(10);
q.enqueue(20);
q.enqueue(30);
q.displayFront();
q.dequeue();
q.displayFront();
q.dequeue();
q.dequeue();
q.dequeue(); // Queue underflow
