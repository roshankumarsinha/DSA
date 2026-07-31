// Implement a Deque (doubly ended queue) using an array with:
// insertFront(value), insertRear(value), deleteFront(), deleteRear(),
// getFront(), getRear(), isFull(), isEmpty()

const SIZE = 5;

class Deque {
  constructor() {
    this.arr = new Array(SIZE);
    this.front = -1;
    this.rear = -1;
  }

  isEmpty() {
    return this.front === -1;
  }

  isFull() {
    return (
      (this.front === 0 && this.rear === SIZE - 1) ||
      (this.rear + 1) % SIZE === this.front
    );
  }

  // Insert at the front
  insertFront(value) {
    if (this.isFull()) {
      console.log(`Dequeue Overflow! Cannot insert ${value} at the front.`);
      return;
    }
    if (this.isEmpty()) {
      this.front = this.rear = 0;
    } else if (this.front === 0) {
      this.front = SIZE - 1; // wrap around to the end
    } else {
      this.front--;
    }
    this.arr[this.front] = value;
  }

  // Insert at the rear
  insertRear(value) {
    if (this.isFull()) {
      console.log(`Dequeue Overflow! Cannot insert ${value} at the rear.`);
      return;
    }
    if (this.isEmpty()) {
      this.front = this.rear = 0;
    } else if (this.rear === SIZE - 1) {
      this.rear = 0; // wrap around to the beginning
    } else {
      this.rear++;
    }
    this.arr[this.rear] = value;
  }

  // Delete from the front
  deleteFront() {
    if (this.isEmpty()) {
      console.log("Dequeue Underflow! Cannot delete from the front.");
      return;
    }
    console.log("Deleted from front:", this.arr[this.front]);
    if (this.front === this.rear) {
      this.front = this.rear = -1; // only one element
    } else if (this.front === SIZE - 1) {
      this.front = 0; // wrap around
    } else {
      this.front++;
    }
  }

  // Delete from the rear
  deleteRear() {
    if (this.isEmpty()) {
      console.log("Dequeue Underflow! Cannot delete from the rear.");
      return;
    }
    console.log("Deleted from rear:", this.arr[this.rear]);
    if (this.front === this.rear) {
      this.front = this.rear = -1; // only one element
    } else if (this.rear === 0) {
      this.rear = SIZE - 1; // wrap around
    } else {
      this.rear--;
    }
  }

  getFront() {
    if (this.isEmpty()) {
      console.log("Dequeue is empty!");
      return;
    }
    console.log("Front element:", this.arr[this.front]);
  }

  getRear() {
    if (this.isEmpty()) {
      console.log("Dequeue is empty!");
      return;
    }
    console.log("Rear element:", this.arr[this.rear]);
  }

  display() {
    if (this.isEmpty()) {
      console.log("Dequeue is empty!");
      return;
    }
    const elements = [];
    let i = this.front;
    while (true) {
      elements.push(this.arr[i]);
      if (i === this.rear) break;
      i = (i + 1) % SIZE;
    }
    console.log("Dequeue elements:", elements.join(" "));
  }
}

// Driver code
const dq = new Deque();
dq.insertRear(10);
dq.insertRear(20);
dq.insertFront(5);
dq.insertFront(1);
dq.display();
dq.getFront();
dq.getRear();
dq.deleteFront();
dq.display();
dq.deleteRear();
dq.display();
dq.insertRear(30);
dq.insertRear(40);
dq.insertFront(0); // overflow example
dq.display();
