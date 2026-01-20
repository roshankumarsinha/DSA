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





// =====================================================
// MAJORITY ELEMENTS (> N/3 times) - EXTENDED MOORE'S VOTING ALGORITHM
// =====================================================

/*
    Problem: Given an array of size n, find all elements that appear more than n/3 times.

    Example:
    Input: nums = [3, 2, 3]
    Output: [3]

    Input: nums = [1, 1, 1, 3, 3, 2, 2, 2]
    Output: [1, 2]

    =====================================================
    INTUITION (Relation to Moore's Algorithm):
    =====================================================
    
    Standard Moore's Algorithm (n/2):
    - At most 1 element can appear more than n/2 times
    - We track 1 candidate with 1 counter
    
    Extended Moore's Algorithm (n/3):
    - At most 2 elements can appear more than n/3 times
      (Why? If 3 elements each appear > n/3 times, total > n. Impossible!)
    - We track 2 candidates with 2 counters
    
    The core idea remains the same:
    - Majority elements will "survive" the voting process
    - Elements that appear frequently enough cannot be completely cancelled out

    =====================================================
    APPROACH:
    =====================================================
    Phase 1: Find Candidates (Modified Moore's Voting)
    1. Maintain two candidates (cand1, cand2) and two counters (cnt1, cnt2)
    2. For each element:
       a. If element == cand1 → cnt1++
       b. Else if element == cand2 → cnt2++
       c. Else if cnt1 == 0 → cand1 = element, cnt1 = 1
       d. Else if cnt2 == 0 → cand2 = element, cnt2 = 1
       e. Else → cnt1--, cnt2-- (cancel one vote from each)

    Phase 2: Validate Candidates
    1. Count actual occurrences of cand1 and cand2
    2. Return those with count > n/3

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [1, 1, 1, 3, 3, 2, 2, 2]
    n = 8, so we need count > 8/3 = 2 (i.e., count >= 3)

    Initial: cand1 = 0, cnt1 = 0, cand2 = 0, cnt2 = 0

    i=0, num=1: cnt1=0, so cand1=1, cnt1=1
                State: cand1=1(1), cand2=0(0)

    i=1, num=1: num==cand1, so cnt1++
                State: cand1=1(2), cand2=0(0)

    i=2, num=1: num==cand1, so cnt1++
                State: cand1=1(3), cand2=0(0)

    i=3, num=3: cnt2=0, so cand2=3, cnt2=1
                State: cand1=1(3), cand2=3(1)

    i=4, num=3: num==cand2, so cnt2++
                State: cand1=1(3), cand2=3(2)

    i=5, num=2: Neither match, cnt1>0, cnt2>0 → cnt1--, cnt2--
                State: cand1=1(2), cand2=3(1)

    i=6, num=2: Neither match, cnt1>0, cnt2>0 → cnt1--, cnt2--
                State: cand1=1(1), cand2=3(0)

    i=7, num=2: cnt2=0, so cand2=2, cnt2=1
                State: cand1=1(1), cand2=2(1)

    Candidates: 1 and 2

    Validation:
    - Count of 1 = 3 > 8/3 ✓
    - Count of 2 = 3 > 8/3 ✓

    Output: [1, 2] ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Two passes through array
    SPACE COMPLEXITY: O(1) - Only using variables (output space not counted)
    =====================================================
*/

vector<int> majorityElementN3(vector<int>& nums) {
    int n = nums.size();
    
    // Phase 1: Find potential candidates
    int cand1 = 0, cand2 = 0;
    int cnt1 = 0, cnt2 = 0;
    
    for (int num : nums) {
        // Important: Check equality first before checking counts
        if (num == cand1) {
            cnt1++;
        } else if (num == cand2) {
            cnt2++;
        } else if (cnt1 == 0) {
            cand1 = num;
            cnt1 = 1;
        } else if (cnt2 == 0) {
            cand2 = num;
            cnt2 = 1;
        } else {
            // Current element is different from both candidates
            // Cancel one vote from each
            cnt1--;
            cnt2--;
        }
    }
    
    // Phase 2: Validate candidates
    cnt1 = 0;
    cnt2 = 0;
    for (int num : nums) {
        if (num == cand1) cnt1++;
        else if (num == cand2) cnt2++;
    }
    
    vector<int> result;
    if (cnt1 > n / 3) result.push_back(cand1);
    if (cnt2 > n / 3) result.push_back(cand2);
    
    return result;
}