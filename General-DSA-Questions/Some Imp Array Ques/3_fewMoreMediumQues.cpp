/*
    =====================================================
    REARRANGE ARRAY ELEMENTS BY SIGN
    =====================================================

    Problem: Given an array with equal number of positive and negative elements,
    rearrange them in alternating positive-negative order while maintaining 
    their relative order.

    This question is almost similar to "Move All Zeros to End of Array" where instead of zeros,
    we are dealing with positive and negative numbers. The approach is similar, but we need to handle
    the relative order of elements.

    Example:
    Input:  [3, 1, -2, -5, 2, -4]
    Output: [3, -2, 1, -5, 2, -4]
    
    - Positives in original order: 3, 1, 2
    - Negatives in original order: -2, -5, -4
    - Alternating: 3, -2, 1, -5, 2, -4

    =====================================================
    INTUITION:
    =====================================================
    
    Since we need alternating pattern starting with positive:
    - Positive elements go to indices: 0, 2, 4, 6, ...
    - Negative elements go to indices: 1, 3, 5, 7, ...
    
    We use TWO POINTERS:
    - posIndex = 0 (tracks next position for positive)
    - negIndex = 1 (tracks next position for negative)
    
    As we traverse, we place each element at its designated position
    and increment the respective pointer by 2.

    =====================================================
    APPROACH:
    =====================================================
    1. Create result array of same size
    2. Initialize posIndex = 0, negIndex = 1
    3. Traverse original array:
       a. If element > 0 → place at result[posIndex], posIndex += 2
       b. If element < 0 → place at result[negIndex], negIndex += 2
    4. Return result

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [3, 1, -2, -5, 2, -4]
    
    posIndex = 0, negIndex = 1, result = [_, _, _, _, _, _]

    i=0, num=3 (positive):
        result[0] = 3, posIndex = 2
        result = [3, _, _, _, _, _]

    i=1, num=1 (positive):
        result[2] = 1, posIndex = 4
        result = [3, _, 1, _, _, _]

    i=2, num=-2 (negative):
        result[1] = -2, negIndex = 3
        result = [3, -2, 1, _, _, _]

    i=3, num=-5 (negative):
        result[3] = -5, negIndex = 5
        result = [3, -2, 1, -5, _, _]

    i=4, num=2 (positive):
        result[4] = 2, posIndex = 6
        result = [3, -2, 1, -5, 2, _]

    i=5, num=-4 (negative):
        result[5] = -4, negIndex = 7
        result = [3, -2, 1, -5, 2, -4]

    Output: [3, -2, 1, -5, 2, -4] ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass
    SPACE COMPLEXITY: O(n) - Result array
    =====================================================
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> rearrangeBySign(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    
    int posIndex = 0;  // Positions: 0, 2, 4, ...
    int negIndex = 1;  // Positions: 1, 3, 5, ...
    
    for (int num : arr) {
        if (num > 0) {
            result[posIndex] = num;
            posIndex += 2;
        } else {
            result[negIndex] = num;
            negIndex += 2;
        }
    }
    
    return result;
}





/*
    =====================================================
    LONGEST CONSECUTIVE SEQUENCE IN AN ARRAY
    =====================================================

    Problem: Given an unsorted array of integers, find the length of the 
    longest consecutive elements sequence.

    Example:
    Input: nums = [100, 4, 200, 1, 3, 2]
    Output: 4
    Explanation: Longest consecutive sequence is [1, 2, 3, 4]. Length = 4

    Input: nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
    Output: 9
    Explanation: Sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8]. Length = 9

    =====================================================
    INTUITION:
    =====================================================
    
    Brute Force would be O(n log n) using sorting.
    
    Optimal: Use a HASHMAP for O(1) lookups!
    
    Key Insight: A number is the START of a sequence only if (num - 1) 
    does NOT exist in the map.
    
    Example: In [100, 4, 200, 1, 3, 2]
    - 1 is a start because 0 doesn't exist
    - 2 is NOT a start because 1 exists
    - 3 is NOT a start because 2 exists
    - 4 is NOT a start because 3 exists
    
    So we only count sequence length starting from "sequence starters"!

    IMPORTANT (Avoiding TLE):
    - If we iterate over the original array, duplicates cause redundant processing
    - Solution: Iterate over UNIQUE keys in the map instead
    - This ensures each unique number is processed only once

    =====================================================
    APPROACH:
    =====================================================
    1. Insert all elements into a HashMap (automatically handles duplicates)
    2. Iterate over unique keys in the map (NOT the original array):
       a. Check if (num - 1) exists in map
       b. If YES → skip (not a sequence start)
       c. If NO → this is a sequence start, count consecutive elements
    3. Track maximum length found

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [100, 4, 200, 1, 3, 2]
    
    HashSet: {100, 4, 200, 1, 3, 2}

    num = 100:
        99 not in set → START of sequence
        Count: 100 ✓, 101 ✗ → length = 1
        maxLen = 1

    num = 4:
        3 in set → NOT a start, skip

    num = 200:
        199 not in set → START of sequence
        Count: 200 ✓, 201 ✗ → length = 1
        maxLen = 1

    num = 1:
        0 not in set → START of sequence
        Count: 1 ✓, 2 ✓, 3 ✓, 4 ✓, 5 ✗ → length = 4
        maxLen = 4

    num = 3:
        2 in set → NOT a start, skip

    num = 2:
        1 in set → NOT a start, skip

    Output: 4 ✓

    =====================================================
    WHY IS THIS O(n)?
    =====================================================
    Each element is visited at most TWICE:
    - Once when checking if it's a start
    - Once when counting (only if it's part of a sequence)
    
    Total operations = O(2n) = O(n)

    =====================================================
    TIME COMPLEXITY:  O(n) - Each element visited at most twice
    SPACE COMPLEXITY: O(n) - HashSet storage
    =====================================================
*/

int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Step 1: Insert all elements into HashMap
    unordered_map<int, bool> numMap;
    for (int num : nums) {
        numMap[num] = true;  // true = not yet processed as sequence start
    }
    
    int maxLen = 0;
    
    // Step 2: Iterate over UNIQUE keys in map (avoids duplicate processing)
    for (auto pair : numMap) {
        int num = pair.first;
        
        // Check if this is the start of a sequence
        if (!numMap[num - 1]) {     // We could have wriiten numMap[num] = false;
            // num - 1 doesn't exist, so num is a sequence start
            int currentNum = num;
            int currentLen = 1;
            
            // Count consecutive elements
            while (numMap.find(currentNum + 1) != numMap.end()) {
                currentNum++;
                currentLen++;
            }
            
            maxLen = max(maxLen, currentLen);
        }
    }
    
    return maxLen;
}
