// Implement a stack using an array in JavaScript.

// Notes : https://takeuforward.org/data-structure/implement-stack-using-array/

// JavaScript note: C++ allocated a fixed `new int[size]`. Here we use a plain array with an
// explicit `top` index to mirror the array-based implementation (rather than relying on JS's
// built-in push/pop). A JS array grows dynamically, so there is no fixed capacity limit.
class Stack {
  constructor() {
    this.top = -1;
    this.arr = [];
  }

  push(x) {
    this.top++;
    this.arr[this.top] = x;
  }

  pop() {
    const x = this.arr[this.top];
    this.top--;
    return x;
  }

  Top() {
    return this.arr[this.top];
  }

  Size() {
    return this.top + 1; // 0-based indexing, so size is top + 1
  }
}

// Driver code
const s = new Stack();
s.push(6);
s.push(3);
s.push(7);
console.log("Top of stack before deleting any element:", s.Top()); // 7
console.log("Size of stack before deleting any element:", s.Size()); // 3
console.log("The element deleted is:", s.pop()); // 7
console.log("Size of stack after deleting an element:", s.Size()); // 2
console.log("Top of stack after deleting an element:", s.Top()); // 3
