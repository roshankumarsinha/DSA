// Write a function to find minimize the maximum number of pages allocated to a book.

// 📘 Problem Statement
// You are given an array books[] where books[i] represents the number of pages in the i-th book, and an integer M — the number of students.
// Your task is to allocate books to M students such that:
//    Each student gets at least one book.
//    Each student gets contiguous books.
//    Each book is assigned to exactly one student.
//    Goal: Minimize the maximum number of pages assigned to a student.

// Notes link : https://takeuforward.org/data-structure/allocate-minimum-number-of-pages/
// Video link : https://www.youtube.com/watch?v=Z0hwjftStI4


// For these kind of problems we need to find a range/scale in which our answer lies and then perform binary search on that range to find the optimal answer.
// Before applying binary search, think of brute force which is linear search on the answer space, and then optimize it using binary search.

// 🔍 Key Observations:
// 1. If you assign all books to one student, the number of pages will be the sum of all books.
// 2. If you assign each book to a different student, the maximum pages assigned will be the maximum book size.
// 3. So the answer lies between:
//    min = max(book[i]) and max = sum(book[i])
// 4. This mean we have to search for a value between min and max that satisfies the condition of allocating books to M students.
// 5. One way to do this is using linear search, but that would be inefficient.

// 🤔 How to Find the Right Answer?
// Instead of checking every possible way to divide books (which is too slow), we binary search the answer — the "maximum number of pages" a student might get.

// ✅ Idea:
// "For a given value mid, can we split the books among M students such that no student gets more than mid pages?"
//  1.  If yes, then maybe we can do even better → try a smaller mid
//  2.  If no, it means our mid is too small → try a bigger mid
// We continue this process using binary search until we find the minimum mid that works.

// 📦 Analogy:
// Think of this like dividing heavy boxes among M people such that no one carries too much.
//  1.  If the current weight limit (mid) is too low, people can’t carry all the boxes → increase it.
//  2.  If it's doable, maybe they can carry less → try reducing the limit.
// Eventually, you find the smallest weight limit that works — that's your answer.

// Note, the number of students will be decreasing as we move right in the seacrh space. The last number will be student 1 and he can take all the books.

// Algorithm:
// 1. If m > n: In this case, book allocation is not possible and so, we will return -1.
// 2. Place the 2 pointers i.e. low and high: Initially, we will place the pointers. The pointer low will point to max(arr[]) and the high will point to sum(arr[]).
// 3. Calculate the ‘mid’: Now, inside the loop, we will calculate the value of ‘mid’ using the following formula:
//    mid = (low+high) / 2 
// 4. Eliminate the halves based on the number of students returned by countStudents():
//    We will pass the potential number of pages, represented by the variable 'mid', to the ‘countStudents()' function.
//    This function will return the number of students to whom we can allocate the books.
//    a.  If students > m: On satisfying this condition, we can conclude that the number ‘mid’ is smaller than our answer.
//        So, we will eliminate the left half and consider the right half(i.e. low = mid+1).
//    b.  Otherwise, the value mid is one of the possible answers. But we want the minimum value.
//        So, we will eliminate the right half and consider the left half(i.e. high = mid-1).
// 5. Finally, outside the loop, we will return the value of low as the pointer will be pointing to the answer.

#include <iostream>
#include <vector>
using namespace std;

int countStudents(vector<int> &books, int mid) {  // mid is the maximum number of pages a student can take
    int students = 1; // Start with one student
    int pagesAllocated = 0; // Pages allocated to the current student
    
    for (int i = 0; i < books.size(); i++) {  // Iterate through each book
      if (pagesAllocated + books[i] <= mid) { // If adding the current book doesn't exceed mid
            pagesAllocated += books[i]; // Allocate pages to the current student
        } else {
            students++; // Need a new student
            pagesAllocated = books[i]; // Allocate the current book to the new student
        }
    }
    
    return students; // Return the total number of students needed
}

int allocateBooks(vector<int> &books, int m) {
    if (m > books.size()) return -1; // Not enough books for students, if number of students is greater than number of books

    // Calculate low and high for binary search
    int low = books[0]; // Minimum pages a student can take is the largest book
    int high = books[0]; // Maximum pages a student can take is the sum of all books
    for (int i = 1; i < books.size(); i++) {
        low = max(low, books[i]); // Find the maximum book size
        high += books[i]; // Sum of all books
    }

    int result = -1;  // Initialize result to -1
    while (low <= high) {
        int mid = low + (high - low) / 2; // Calculate mid

        int students = countStudents(books, mid); // Count how many students can be allocated with mid pages
        if (students > m) { // If more students are needed than available, then mid is too small, it can't be the answer, so we need to decrease students so that it atleast becomes equal to m, we increase mid
            low = mid + 1; // Increase the minimum limit, and move to the right half so that we can decrease the students
        } else { // If we can allocate books to m or fewer students
            result = mid; // Update result with the current mid, This can be a potential answer
            // We try to find a smaller maximum page allocation
            // So, we move to the left half
            high = mid - 1; // Try to find a smaller maximum page allocation
        }
    }
    return result; // Return the minimum maximum pages found
}

int main() {
    vector<int> books = {12, 34, 67, 90}; // Example book pages
    int m = 2; // Number of students

    int result = allocateBooks(books, m);
    if (result != -1) {
        cout << "Minimum number of pages allocated to a student: " << result << endl;
    } else {
        cout << "Allocation not possible." << endl;
    }

    return 0;
}

// Time Complexity: O(n log(sum(books))) - where n is the number of books and sum(books) is the maximum possible pages.
// Space Complexity: O(1) - We are using a constant amount of space for variables.