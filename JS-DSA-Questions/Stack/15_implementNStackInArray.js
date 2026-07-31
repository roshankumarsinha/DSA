// Implement N stacks in a single array.

// Video link : https://www.youtube.com/watch?v=lrSXKLmnMV8&list=PLDzeHZWIZsTryvtXdMr6rPh4IDexB5NIA&index=63

// Design a data structure implementing N stacks in a single array of size S such that each stack
// supports push, pop, top, and isEmpty in O(1), and the array is shared dynamically (no fixed
// division of space).

// Intuition:
// 1. arr[] stores all values.
// 2. top[] stores the top index of each of the N stacks (init -1).
// 3. next[] serves double duty:
//    - For free slots, next[i] points to the next free slot.
//    - For occupied slots, next[i] points to the previous element in the same stack.
// 4. freeSpot points to the first free slot (init 0).

// JavaScript note: C++ used vectors sized with resize; here we use Array(...).fill(...).
class NStack {
  constructor(N, S) {
    this.n = N;
    this.s = S;
    this.arr = new Array(S);
    this.top = new Array(N).fill(-1); // all stacks empty
    this.next = new Array(S);

    for (let i = 0; i < S - 1; i++) {
      this.next[i] = i + 1; // free list chaining
    }
    this.next[S - 1] = -1; // end of free list
    this.freeSpot = 0;
  }

  // Push value x to the m-th stack (0-based)
  push(x, m) {
    if (this.freeSpot === -1) {
      return false; // overflow
    }

    const index = this.freeSpot;
    this.freeSpot = this.next[index]; // advance free list

    this.arr[index] = x;
    this.next[index] = this.top[m]; // link to previous top
    this.top[m] = index; // new top
    return true;
  }

  // Pop from the m-th stack (reverse of push)
  pop(m) {
    if (this.top[m] === -1) {
      return -1; // underflow
    }

    const index = this.top[m];
    this.top[m] = this.next[index]; // move top down
    this.next[index] = this.freeSpot; // return slot to free list
    this.freeSpot = index;
    return this.arr[index];
  }

  // Peek at the top of the m-th stack
  peek(m) {
    if (this.top[m] === -1) return -1;
    return this.arr[this.top[m]];
  }

  isEmpty(m) {
    return this.top[m] === -1;
  }
}

// Driver code
const ns = new NStack(3, 6);
ns.push(10, 0);
ns.push(20, 0);
ns.push(30, 1);
console.log(ns.pop(0)); // 20
console.log(ns.peek(0)); // 10
console.log(ns.pop(1)); // 30
console.log(ns.isEmpty(2)); // true
