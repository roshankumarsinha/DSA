// Write a class to implement N stacks in a single array in C++.

// Video link : https://www.youtube.com/watch?v=lrSXKLmnMV8&list=PLDzeHZWIZsTryvtXdMr6rPh4IDexB5NIA&index=63

// Design a data structure that implements N stacks in a single array of size S such that:
//    Each stack supports push, pop, top, and isEmpty in O(1) time.
//    The array is shared among all stacks dynamically (no fixed division of size).


// Intiution:
// To dynamically allocate space for N stacks inside a single array:
//    1.  Use a main array arr[] to store all values.
//    2.  Use a top array top[] to store the top index of each of the N stacks.
//    3.  Use a next array next[] to:
//      a.  Maintain a free list of available slots.
//      b.  Link elements within each stack (like linked list via array).

// ✅ Data Structures
// Name	        Purpose
// arr[]	   Actual storage of elements
// top[]	   Stores index of the top of each stack
// next[]	   Tracks next free slot or next element index, if arr is empty then next tells next free slot, and if arr is not empty then next tells next element index
// freeSpot	   Points to the next available slot in arr[] (initially points to the first index of arr[])


#include <iostream>
#include <vector>
using namespace std;

class NStack {
private:
    int n, s; // n = number of stacks, s = size of array
    vector<int> arr;    // actual array to store values
    vector<int> top;    // stores indices of top elements of all stacks
    vector<int> next;   // helps in linking and free list
    int freeSpot;       // beginning index of free list

public:
    NStack(int N, int S) {
        n = N;
        s = S;
        arr.resize(S);
        top.resize(N, -1);  // Initialize all stack tops to -1 (indicating empty stacks)
        next.resize(S);

        for (int i = 0; i < S - 1; i++) {
            next[i] = i + 1;  // Next free index points to the next index
        }
        next[S - 1] = -1;  // end of free list, then last index points to -1
        freeSpot = 0; // Initially, the first index is free
    }

    // Push value x to m-th stack (0-based index)
    bool push(int x, int m) {
        if (freeSpot == -1) { // No free space available
            return false; // Overflow
        }

        int index = freeSpot;      // Find indes to insert the value
        freeSpot = next[index];    // Find index of next free spot

        arr[index] = x;            // insert value into the array
        next[index] = top[m];      // link previous top, // so next[index] points to the previous top of m-th stack
        top[m] = index;            // update top, // so top[m] now points to the new top of m-th stack
        return true;  // Successfully pushed
    }

    // Pop from m-th stack (0-based index), For Pop operation just reverse all the push operation
    int pop(int m) {
        if (top[m] == -1) {
            return -1; // Underflow
        }

        int index = top[m];       // index to pop
        top[m] = next[index];     // update top
        next[index] = freeSpot;       // add index back to free list
        freeSpot = index;       // update freeSpot to the popped index
        return arr[index]; // return popped value
    }

    // Peek top of m-th stack
    int peek(int m) {
        if (top[m] == -1) {
            return -1;
        }
        return arr[top[m]];
    }

    // Check if m-th stack is empty
    bool isEmpty(int m) {
        return top[m] == -1;
    }
};
