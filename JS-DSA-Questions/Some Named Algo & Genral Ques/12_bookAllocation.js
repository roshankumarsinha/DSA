// Minimize the maximum number of pages allocated to a student ("Allocate Minimum Number of Pages").

// 📘 Problem Statement
// Given books[] where books[i] is the number of pages in the i-th book, and M students, allocate
// books so that:
//    - Each student gets at least one book.
//    - Each student gets contiguous books.
//    - Each book is assigned to exactly one student.
// Goal: Minimize the maximum number of pages assigned to any student.

// Notes link : https://takeuforward.org/data-structure/allocate-minimum-number-of-pages/
// Video link : https://www.youtube.com/watch?v=Z0hwjftStI4

// For these problems, find a range in which the answer lies, then binary search on that range.
// The answer lies between min = max(books[i]) and max = sum(books[i]).

// Idea: "For a given value mid, can we split the books among M students so no student gets more
// than mid pages?" If yes → try a smaller mid; if no → try a bigger mid.

// Algorithm:
// 1. If m > n, allocation is impossible → return -1.
// 2. low = max(books), high = sum(books).
// 3. mid = (low + high) / 2. Use countStudents(mid) to check feasibility.
//    a. If students > m, mid is too small → low = mid + 1.
//    b. Otherwise mid is a candidate; try to do better → high = mid - 1.
// 4. Return the best answer found.

function countStudents(books, mid) {
  // mid = maximum pages a student can take
  let students = 1;
  let pagesAllocated = 0;

  for (let i = 0; i < books.length; i++) {
    if (pagesAllocated + books[i] <= mid) {
      pagesAllocated += books[i]; // allocate to the current student
    } else {
      students++; // need a new student
      pagesAllocated = books[i];
    }
  }

  return students;
}

function allocateBooks(books, m) {
  if (m > books.length) return -1; // not enough books for the students

  let low = books[0];
  let high = books[0];
  for (let i = 1; i < books.length; i++) {
    low = Math.max(low, books[i]); // max single book
    high += books[i]; // total pages
  }

  let result = -1;
  while (low <= high) {
    const mid = low + Math.floor((high - low) / 2);

    const students = countStudents(books, mid);
    if (students > m) {
      low = mid + 1; // mid too small; increase it
    } else {
      result = mid; // candidate answer; try smaller
      high = mid - 1;
    }
  }
  return result;
}

const books = [12, 34, 67, 90];
const m = 2;
const result = allocateBooks(books, m);
console.log(result !== -1 ? `Minimum pages allocated to a student: ${result}` : "Allocation not possible."); // 113

// Time Complexity: O(n log(sum(books))). Space Complexity: O(1).
