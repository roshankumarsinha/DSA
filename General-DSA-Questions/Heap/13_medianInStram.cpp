// You are given a stream of integers (one by one), and after each new number, you need to return the median of all elements so far.

// Median is the middle value in a sorted list of numbers.
// If the list has an even number of elements, the median is the average of the two middle numbers.


// Key Idea :-
// 1. To maintain a running median, we use two heaps:
//    a.  Max Heap → stores the smaller half of the numbers
//    b.  Min Heap → stores the larger half of the numbers
// 2. Heaps are balanced such that their sizes differ by at most 1

// ✨ Why Two Heaps?
// 1. All numbers in max heap are less than or equal to all numbers in min heap
// 2. The size of heaps is balanced so the median can be:
//    a.  Top of max heap (if odd number of elements). We are assuming maxHeap will always have more elements than minHeap or they will be equal in size.
//    b.  Average of tops of both heaps (if even number)

//            Invariant                              |                   Maintains
// maxHeap.size() >= minHeap.size()                  |   Makes median easy to fetch
// All elements in maxHeap ≤ all elements in minHeap | So median lies between their tops

// Approach:
// 1. Insertion: Let’s say a new number num comes in.
//    a.  If num is <= maxHeap.top() → It belongs to the left half
//    b.  Else → It belongs to the right half
// 2. Balance the heaps: After insertion, we may have imbalance: We need to balance the heaps as maxHeap.size() - minHeap.size() ≤ 1
//    a.  If maxHeap.size() > minHeap.size() + 1 → Move the top of maxHeap to minHeap
//    b.  If minHeap.size() > maxHeap.size() → Move the top of minHeap to maxHeap
// 3. Median Calculation:
//    a.  If both heaps are equal in size → median is the average of both tops
//    b.  Else → median is top of the heap with more elements (which is maxHeap)

// 4. Time Complexity: 
//    Operation       |     Time Complexity
//    addNum(int num) |       O(log n)
//    findMedian()    |         O(1)
// 🔁 Total Time for n numbers:
// If you process n numbers from the stream:
// Inserting each number: n × O(log n) = O(n log n)
// Getting median after each: n × O(1) = O(n)
// ✅ So overall for n numbers: O(n log n)

// 5. Space Complexity: O(n) for storing the elements in the heaps

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder {
  private:
    priority_queue<int> maxHeap; // Max-heap for the smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap for the larger half
  public:

    // Function to add a number to the data structure
    void addNum(int num) {
        // Add to maxHeap (smaller half)
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else { // Add to minHeap (larger half)
            minHeap.push(num); // Add to minHeap (larger half)
        }

        // Balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) {  // maxHeap is too large
            minHeap.push(maxHeap.top()); // Move top of maxHeap to minHeap
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) { // minHeap is too large
            maxHeap.push(minHeap.top()); // Move top of minHeap to maxHeap
            minHeap.pop();
        }
    }

    // Function to find the median of the numbers added so far
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) { // maxHeap has more elements, and n is odd
            return maxHeap.top(); // Return the top of maxHeap
        } else { // Both heaps are equal in size, and n is even
            return (maxHeap.top() + minHeap.top()) / 2.0; // Return the average of both tops
        }
    }
};

int main() {
    MedianFinder mf;
    vector<int> nums = {5, 15, 1, 3};
    for (int num : nums) {
        mf.addNum(num); // Add each number to the data structure
        cout << "Current Median: " << mf.findMedian() << endl; // Print the current median
    }

    return 0;
}

// Output:
// Median after 5: 5
// Median after 15: 10
// Median after 1: 5
// Median after 3: 4


// 🔍 Visual Example
// Stream: 5, 15, 1, 3

// After 1st input 5:
// maxHeap = [5]
// minHeap = []
// Median = 5

// After 2nd input 15:
// 15 > 5 → insert to minHeap
// maxHeap = [5], minHeap = [15]
// Sizes are equal → Median = (5 + 15)/2 = 10

// After 3rd input 1:
// 1 < 5 → insert to maxHeap
// maxHeap = [5, 1], minHeap = [15]
// maxHeap has more → Median = 5

// After 4th input 3:
// 3 < 5 → insert to maxHeap
// Now maxHeap too big → move top to minHeap
// maxHeap = [3, 1], minHeap = [5, 15]
// Median = (3 + 5)/2 = 4