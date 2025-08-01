// Write a function for Moore's algorithm that finds the majority element in an array of integers.
// A majority element is an element that appears more than n/2 times where n is the size of the array.

// Example:
// Input: arr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4}
// Output: 4
// Explanation: The element 4 appears 5 times which is more than n/2.

// Video link : https://www.youtube.com/watch?v=_xqIp2rj8bo&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=11

// ✅ Intuition:
// If an element appears more than half the times in the array, it will "outvote" all other elements combined.
// So, we can make one pass to find a candidate, and another to verify it.

// ✅ Steps:
// Candidate Selection Phase:
//  1.  Initialize count = 0 and candidate = None.
//  2.  For each element:
//      a.  If count == 0, set candidate = current element.
//      b.  If current element == candidate → count++
//      c.  Else → count--
// Validation Phase (optional for interview problems): (This step is only needed if you want to confirm the candidate is indeed a majority element)
//  1.  Count occurrences of candidate in array.
//  2.  If it's > n/2, return candidate.
//  3.  Else, return -1 (or say "no majority element").

#include <iostream>
#include <vector>

using namespace std;

int moore(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    for (int value: nums) {
        if (count == 0) {
            candidate = value;
        }
        // You can also write this as count += (value == candidate) ? 1 : -1;
        if (value == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // Optional: Validate the candidate
    count = 0;
    for (int value: nums) {
        if (value == candidate) {
            count++;
        }
    }
    if (count <= nums.size() / 2) {
        return -1; // No majority element found
    }
    // If you want to return the candidate only if it's a majority element
    // you can uncomment the following line:
    // if (count > nums.size() / 2) return candidate;
    return candidate;   
}