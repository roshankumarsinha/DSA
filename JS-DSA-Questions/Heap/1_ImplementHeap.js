// Implement a heap (max-heap here) using an array, with insertion, deletion, and display.

// Insertion (O(log N)):
// 1. Add the new element at the end.
// 2. Bubble it up: while it's greater than its parent (index/2 in 1-based indexing), swap.

// Deletion (O(log N)):
// 1. Replace the root with the last element and shrink the size.
// 2. Bubble the new root down: swap with the larger child until the heap property holds.

// JavaScript note: this uses 1-based indexing like the C++ version (index 0 is unused), and a
// plain array as backing storage. Swaps use destructuring instead of std::swap.
class MaxHeap {
  constructor(capacity) {
    this.capacity = capacity;
    this.heap = new Array(capacity + 1);
    this.heap[0] = -1; // unused (1-based indexing)
    this.size = 0;
  }

  insertion(value) {
    if (this.size === this.capacity) {
      console.log(`Heap is full. Cannot insert ${value}`);
      return;
    }

    this.size++;
    this.heap[this.size] = value;
    let index = this.size;

    // Bubble up
    while (index > 1) {
      const parentIndex = Math.floor(index / 2);
      if (this.heap[parentIndex] < this.heap[index]) {
        [this.heap[parentIndex], this.heap[index]] = [this.heap[index], this.heap[parentIndex]];
        index = parentIndex;
      } else {
        break;
      }
    }
  }

  deletion() {
    if (this.size === 0) {
      console.log("Heap is empty. Cannot delete.");
      return -1;
    }

    const root = this.heap[1];
    this.heap[1] = this.heap[this.size]; // move last element to root
    this.size--;

    // Bubble down
    let index = 1;
    while (index < this.size) {
      const leftChildIndex = 2 * index;
      const rightChildIndex = 2 * index + 1;
      let largestIndex = index;

      if (leftChildIndex < this.size && this.heap[leftChildIndex] > this.heap[largestIndex]) {
        largestIndex = leftChildIndex;
      }
      if (rightChildIndex < this.size && this.heap[rightChildIndex] > this.heap[largestIndex]) {
        largestIndex = rightChildIndex;
      }

      if (largestIndex !== index) {
        [this.heap[index], this.heap[largestIndex]] = [this.heap[largestIndex], this.heap[index]];
        index = largestIndex;
      } else {
        break;
      }
    }

    return root;
  }

  display() {
    console.log("Heap elements:", this.heap.slice(1, this.size + 1).join(" "));
  }
}

// Driver code
const maxHeap = new MaxHeap(10);
maxHeap.insertion(50);
maxHeap.insertion(30);
maxHeap.insertion(40);
maxHeap.insertion(10);
maxHeap.insertion(20);
maxHeap.insertion(60);
maxHeap.display();
console.log("Deleted root element:", maxHeap.deletion());
maxHeap.display();
console.log("Deleted root element:", maxHeap.deletion());
maxHeap.display();
