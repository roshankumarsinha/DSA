// Implement a circular queue using an array.

// The modulo operation (% SIZE) implements the circular "wrap around" behavior: when rear reaches
// the end of the array it wraps back to the front if space is available.

const SIZE = 5;

class CircularQueue {
  constructor() {
    this.arr = new Array(SIZE);
    this.front = -1;
    this.rear = -1;
  }

  enqueue(value) {
    // Full when the next position after rear would be front
    if ((this.rear + 1) % SIZE === this.front) {
      console.log(`Queue Overflow! Cannot insert ${value}`);
      return;
    }
    if (this.front === -1) this.front = 0; // first element
    this.rear = (this.rear + 1) % SIZE;
    this.arr[this.rear] = value;
  }

  dequeue() {
    if (this.front === -1) {
      console.log("Queue Underflow! Cannot dequeue");
      return;
    }
    console.log("Dequeued:", this.arr[this.front]);
    if (this.front === this.rear) {
      this.front = this.rear = -1; // queue becomes empty
    } else {
      this.front = (this.front + 1) % SIZE;
    }
  }

  displayFront() {
    if (this.front === -1) {
      console.log("Queue is empty!");
    } else {
      console.log("Front:", this.arr[this.front]);
    }
  }

  displayQueue() {
    if (this.front === -1) {
      console.log("Queue is empty!");
      return;
    }
    const elements = [];
    let i = this.front;
    while (true) {
      elements.push(this.arr[i]);
      if (i === this.rear) break;
      i = (i + 1) % SIZE;
    }
    console.log("Queue elements are:", elements.join(" "));
  }

  isEmpty() {
    return this.front === -1;
  }

  isFull() {
    return (this.rear + 1) % SIZE === this.front;
  }
}

// Driver code
const q = new CircularQueue();
q.enqueue(10);
q.enqueue(20);
q.enqueue(30);
q.enqueue(40);
q.enqueue(50); // overflow (capacity is SIZE-1 usable slots)
q.displayQueue();
q.displayFront();
q.dequeue();
q.displayQueue();
q.enqueue(50); // now possible
q.displayQueue();
q.dequeue();
q.dequeue();
q.dequeue();
q.dequeue();
q.dequeue(); // underflow
