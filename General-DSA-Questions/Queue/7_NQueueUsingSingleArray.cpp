// Write a class that implements 'k' queue using a single array. Implement k Queues in a single array.

// Approach:
// 1. Create an array of size 'n' to store the elements of 'k' queues.
// 2. Create an array 'front' of size 'k' to store the front index of each queue.
//    a. Initialize all the front indices to -1.
// 3. Create an array 'rear' of size 'k' to store the rear index of each queue.
//    a. Initialize all the rear indices to -1.
// 4. Create an array 'next' of size 'n' to links free slots or links the next element in the queue.
//    a. Initialize all the next indices to i+1.
//    b. Initialize the last index of the next array to -1. (Since there is no next element after the last element).
//    c. Initially all the slots are free, so the next array tells which is next free slot available.
// 5. Create a variable 'freeSpot' to store the index of the first free slot.
//    a. Initialize 'freeSpot' to 0.
// 8. Create a constructor to initialize the variables.
// 9. Create a function 'enqueue' to add an element to the queue.
//    a. Check if the queue is full by checking if 'freeSpot' is -1. i.e. no free slot available.
//    b. If the queue is full, return "Queue Overflow!".
//    c. Find the index of the next free slot. Index where the element will be added.
//    d. Update the freeSpot to the next free slot.
//    e. If the queue is empty, update the front index of the queue. If we are adding the first element to the queue.
//    f. If the queue is not empty, link the new element to the previous rear. Rear is the index of the last element in the queue. So we are storing the last rear index in the next array.
//    g. Update the rear index of the queue.
//    h. Store the value in the array.
//    i. Mark this index as -1 in the next array as this space is now occupied.
// 10. Create a function 'dequeue' to remove an element from the queue.
//    a. Check if the queue is empty by checking if the front index is -1.
//    b. If the queue is empty, return "Queue Underflow!".
//    c. Get the index of the front element.
//    d. Update the front index to the next element.
//    e. If the queue is empty, update the rear index to -1.
//    f. Add this slot back to the free list. Link the current free slot to the next free slot.
//    g. Update the freeSpot to the current slot.
//    h. Return the value of the dequeued element.



#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class KQueues {
private:
    int *arr;          // Array to store the elements of k queues
    int *front;        // Array to store the front index of each queue
    int *rear;         // Array to store the rear index of each queue
    int *next;         // Array to link the free slots
    int freeSlot;          // Index of the first free slot

public:
    KQueues(int k, int n) { // k is the number of queues and n is the size of the array
        arr = new int[n];
        front = new int[k];
        rear = new int[k];
        next = new int[n];

        // Initialize the front and rear arrays
        for (int i = 0; i < k; i++) {
            front[i] = rear[i] = -1;
        }

        // Initialize the next array
        for (int i = 0; i < n - 1; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1; // -1 indicates the end of free slots. No next element available
        freeSlot = 0;         // First free slot is 0
    }

    // Enqueue an element into the given queue
    void enqueue(int queueNum, int value) {
      // Check if the queue is full
        if (freeSlot == -1) {
            cout << "Queue Overflow\n";
            return;
        }

        // Get the free slot, index where the element will be added
        int index = freeSlot;

        // Update the free slot to the next free slot
        freeSlot = next[index]; // Update freeSlot to the next free slot

        // Check if it we are adding first element in the queue 
        if (front[queueNum] == -1) {
            // First element in the queue. Store the index in front and not actually the value.
            front[queueNum] = index;
        } else {
            // Link the new element to the previous rear. rear[queueNum] is the index of the last element in the queue. So we are storing the last rear index in next array.
            next[rear[queueNum]] = index;
        }

        // Update rear and store the value
        rear[queueNum] = index;
        // Store the value in the array
        arr[index] = value;
        // Mark this index as -1 in next array as this space is now occupied
        next[index] = -1; // End of the queue
    }

    // Dequeue an element from the given queue
    int dequeue(int queueNum) {
        // Check if the queue is empty
        if (front[queueNum] == -1) {
            cout << "Queue Underflow\n";
            return INT_MIN;
        }

        // Get the index of the front element
        int index = front[queueNum];

        // Front ko aage badaho. front[queueNum] is the index of the front element. So we are storing the next front index in front array.
        front[queueNum] = next[index]; // Update front to the next element

        if (front[queueNum] == -1) {
            rear[queueNum] = -1; // Queue is now empty
        }

        // Add this slot back to the free list. We are linking the current free slot to the next free slot.
        next[index] = freeSlot; // Update next to the current free slot

        // Update the free slot to the current slot
        freeSlot = index;

        return arr[index];
    }
};

int main() {
    int k = 3, n = 10;
    KQueues kQueues(k, n);

    kQueues.enqueue(0, 10);
    kQueues.enqueue(0, 20);
    kQueues.enqueue(1, 30);
    kQueues.enqueue(1, 40);
    kQueues.enqueue(2, 50);

    cout << "Dequeued from queue 0: " << kQueues.dequeue(0) << endl;
    cout << "Dequeued from queue 1: " << kQueues.dequeue(1) << endl;
    cout << "Dequeued from queue 2: " << kQueues.dequeue(2) << endl;

    kQueues.enqueue(2, 60);
    cout << "Dequeued from queue 2: " << kQueues.dequeue(2) << endl;

    return 0;
}


// Explanation with Example:


// Problem Setup
// We have:

// 3 Queues (k = 3)
// Array size (n = 10)
// The operations are as follows:

// Enqueue elements in various queues.
// Dequeue elements from different queues.
// Observe how the internal arrays (arr[], front[], rear[], next[]) are updated after each operation.
// Key Data Structures
// arr[]:
// Stores the actual data for all queues.
// Initial: [_, _, _, _, _, _, _, _, _, _]
// (Empty slots are represented by _.)

// front[]:
// Tracks the front index of each queue.
// Initial: [-1, -1, -1]
// (All queues are initially empty.)

// rear[]:
// Tracks the rear index of each queue.
// Initial: [-1, -1, -1]
// (All queues are initially empty.)

// next[]:
// Tracks the next available index for free slots or links the next element in the queue.
// Initial: [1, 2, 3, 4, 5, 6, 7, 8, 9, -1]
// (Next free slot for each index; -1 indicates the end of free slots.)

// free:
// Tracks the first free index in the arr[].
// Initial: 0.

// Operations and Updates
// Operation 1: Enqueue 10 in Queue 0
// Use free = 0 (first free index).
// Place 10 in arr[0].
// Update front[0] = 0 and rear[0] = 0.
// Update free to next[0] = 1.
// Update next[0] = -1 (end of queue 0).
// State after Operation 1:
// arr[]: [10, _, _, _, _, _, _, _, _, _]
// front[]: [0, -1, -1]
// rear[]: [0, -1, -1]
// next[]: [-1, 2, 3, 4, 5, 6, 7, 8, 9, -1]
// free: 1

// Operation 2: Enqueue 20 in Queue 0
// Use free = 1.
// Place 20 in arr[1].
// Update next[rear[0]] = 1 to link the new element to the queue.
// Update rear[0] = 1.
// Update free to next[1] = 2.
// Update next[1] = -1 (end of queue 0).
// State after Operation 2:
// arr[]: [10, 20, _, _, _, _, _, _, _, _]
// front[]: [0, -1, -1]
// rear[]: [1, -1, -1]
// next[]: [1, -1, 3, 4, 5, 6, 7, 8, 9, -1]
// free: 2

// Operation 3: Enqueue 30 in Queue 1
// Use free = 2.
// Place 30 in arr[2].
// Update front[1] = 2 and rear[1] = 2.
// Update free to next[2] = 3.
// Update next[2] = -1 (end of queue 1).
// State after Operation 3:
// arr[]: [10, 20, 30, _, _, _, _, _, _, _]
// front[]: [0, 2, -1]
// rear[]: [1, 2, -1]
// next[]: [1, -1, -1, 4, 5, 6, 7, 8, 9, -1]
// free: 3

// Operation 4: Dequeue from Queue 0
// Use front[0] = 0.
// Retrieve arr[0] = 10.
// Update front[0] = next[0] = 1.
// Add index 0 back to the free list.
// Update next[0] = free = 3.
// Update free = 0.
// State after Operation 4:
// arr[]: [10, 20, 30, _, _, _, _, _, _, _]
// front[]: [1, 2, -1]
// rear[]: [1, 2, -1]
// next[]: [3, -1, -1, 4, 5, 6, 7, 8, 9, -1]
// free: 0

// Operation 5: Enqueue 40 in Queue 2
// Use free = 0.
// Place 40 in arr[0].
// Update front[2] = 0 and rear[2] = 0.
// Update free to next[0] = 3.
// Update next[0] = -1 (end of queue 2).
// State after Operation 5:
// arr[]: [40, 20, 30, _, _, _, _, _, _, _]
// front[]: [1, 2, 0]
// rear[]: [1, 2, 0]
// next[]: [-1, -1, -1, 4, 5, 6, 7, 8, 9, -1]
// free: 3

// Operation 6: Enqueue 50 in Queue 1
// Use free = 3.
// Place 50 in arr[3].
// Update next[rear[1]] = 3 to link the new element to queue 1.
// Update rear[1] = 3.
// Update free to next[3] = 4.
// Update next[3] = -1 (end of queue 1).
// State after Operation 6:
// arr[]: [40, 20, 30, 50, _, _, _, _, _, _]
// front[]: [1, 2, 0]
// rear[]: [1, 3, 0]
// next[]: [-1, -1, 3, -1, 5, 6, 7, 8, 9, -1]
// free: 4

// Summary
// After performing these operations, the state of the queues is:

// Queue 0: Contains [20]
// Queue 1: Contains [30, 50]
// Queue 2: Contains [40]
