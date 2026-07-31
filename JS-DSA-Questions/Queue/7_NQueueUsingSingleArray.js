// Implement 'k' queues using a single array.

// Approach:
// 1. arr[] of size n stores the elements of all k queues.
// 2. front[] of size k stores the front index of each queue (init -1).
// 3. rear[] of size k stores the rear index of each queue (init -1).
// 4. next[] of size n serves double duty:
//    - For free slots, next[i] points to the next free slot.
//    - For occupied slots, next[i] points to the next element in that queue (-1 at the end).
//    Initially next[i] = i + 1, and next[n-1] = -1.
// 5. freeSlot points to the first free slot (init 0).
//
// enqueue(queueNum, value):
//   - If freeSlot === -1, overflow.
//   - Take index = freeSlot, advance freeSlot = next[index].
//   - If the queue is empty, set front[queueNum] = index; else link next[rear[queueNum]] = index.
//   - rear[queueNum] = index, arr[index] = value, next[index] = -1 (end of queue).
//
// dequeue(queueNum):
//   - If front[queueNum] === -1, underflow.
//   - index = front[queueNum]; advance front[queueNum] = next[index].
//   - If queue becomes empty, rear[queueNum] = -1.
//   - Return the slot to the free list: next[index] = freeSlot; freeSlot = index.

// JavaScript note: C++ used raw `new int[]` arrays; here we use Array(n).fill(...). Returns null
// on underflow instead of INT_MIN.
class KQueues {
  constructor(k, n) {
    this.n = n;
    this.arr = new Array(n);
    this.front = new Array(k).fill(-1);
    this.rear = new Array(k).fill(-1);
    this.next = new Array(n);

    for (let i = 0; i < n - 1; i++) {
      this.next[i] = i + 1;
    }
    this.next[n - 1] = -1; // end of free list
    this.freeSlot = 0;
  }

  enqueue(queueNum, value) {
    if (this.freeSlot === -1) {
      console.log("Queue Overflow");
      return;
    }

    const index = this.freeSlot;
    this.freeSlot = this.next[index]; // advance the free list

    if (this.front[queueNum] === -1) {
      this.front[queueNum] = index; // first element in this queue
    } else {
      this.next[this.rear[queueNum]] = index; // link to previous rear
    }

    this.rear[queueNum] = index;
    this.arr[index] = value;
    this.next[index] = -1; // end of this queue
  }

  dequeue(queueNum) {
    if (this.front[queueNum] === -1) {
      console.log("Queue Underflow");
      return null;
    }

    const index = this.front[queueNum];
    this.front[queueNum] = this.next[index]; // advance front

    if (this.front[queueNum] === -1) {
      this.rear[queueNum] = -1; // queue is now empty
    }

    // Return this slot to the free list
    this.next[index] = this.freeSlot;
    this.freeSlot = index;

    return this.arr[index];
  }
}

// Driver code
const kQueues = new KQueues(3, 10);
kQueues.enqueue(0, 10);
kQueues.enqueue(0, 20);
kQueues.enqueue(1, 30);
kQueues.enqueue(1, 40);
kQueues.enqueue(2, 50);

console.log("Dequeued from queue 0:", kQueues.dequeue(0)); // 10
console.log("Dequeued from queue 1:", kQueues.dequeue(1)); // 30
console.log("Dequeued from queue 2:", kQueues.dequeue(2)); // 50

kQueues.enqueue(2, 60);
console.log("Dequeued from queue 2:", kQueues.dequeue(2)); // 60
