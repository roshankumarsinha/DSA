/*
    =====================================================
    LONGEST SUBARRAY WITH SUM K (Positives and Negatives)
    =====================================================

    Video link : https://www.youtube.com/watch?v=frf7qxiN2qU

    Problem: Given an array containing both positive and negative integers 
    and a sum k, find the length of the longest subarray that sums to k.

    Example:
    Input: arr = [1, -1, 5, -2, 3], k = 3
    Output: 4
    Explanation: Subarray [1, -1, 5, -2] has sum = 3 and length = 4

    =====================================================
    WHAT IS PREFIX SUM?
    =====================================================
    
    Prefix Sum is a technique where we precompute cumulative sums.
    
    For array:    [1, -1, 5, -2, 3]
    Prefix Sum:   [1,  0, 5,  3, 6]
    
    prefix[i] = arr[0] + arr[1] + ... + arr[i]
    
    KEY PROPERTY:
    Sum of subarray from index (i+1) to j = prefix[j] - prefix[i]
    
    This allows us to find sum of ANY subarray in O(1) time!

    =====================================================
    WHERE TO USE PREFIX SUM?
    =====================================================
    
    1. Subarray sum queries - Find sum of any range in O(1)
    2. Finding subarrays with given sum (this problem!)
    3. Count subarrays with sum equals K
    4. Range queries in 2D arrays (2D prefix sum)
    5. Finding equilibrium index
    6. XOR queries on subarrays (prefix XOR)

    =====================================================
    INTUITION:
    =====================================================
    
    If prefix[j] - prefix[i] = k
    Then subarray from (i+1) to j has sum = k
    
    Rearranging: prefix[j] - k = prefix[i]
    
    For each index j:
    - Calculate prefix[j]
    - Check if (prefix[j] - k) exists at some earlier index i
    - If yes, subarray from (i+1) to j has sum = k, length = j - i
    
    We use a HASHMAP to store {prefixSum → earliest index}.
    
    Why earliest index? We want LONGEST subarray!

    =====================================================
    APPROACH:
    =====================================================
    1. Initialize prefixSum = 0, maxLen = 0
    2. Create hashmap: {prefixSum → index}
    3. For each index i:
       a. prefixSum += arr[i]
       b. If prefixSum == k → maxLen = i + 1
       c. If (prefixSum - k) in map → maxLen = max(maxLen, i - map[prefixSum-k])
       d. If prefixSum NOT in map → store {prefixSum: i}
    4. Return maxLen

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: arr = [1, -1, 5, -2, 3], k = 3

    i=0: prefixSum=1, need=-2 (not found), map={1:0}
    i=1: prefixSum=0, need=-3 (not found), map={1:0, 0:1}
    i=2: prefixSum=5, need=2 (not found), map={1:0, 0:1, 5:2}
    i=3: prefixSum=3, prefixSum==k! → maxLen=4, map={1:0, 0:1, 5:2, 3:3}
    i=4: prefixSum=6, need=3 (found at 3) → len=4-3=1, maxLen stays 4

    Output: 4 ✓ (Subarray [1, -1, 5, -2] from index 0 to 3)

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass
    SPACE COMPLEXITY: O(n) - HashMap storage
    =====================================================
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longestSubarrayWithSumK(vector<int>& arr, int k) {
    unordered_map<int, int> prefixMap;  // {prefixSum: earliest index}
    int prefixSum = 0;
    int maxLen = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        prefixSum += arr[i];
        
        // Case 1: Entire subarray from 0 to i has sum = k
        if (prefixSum == k) {
            maxLen = i + 1;
        }
        
        // Case 2: Check if (prefixSum - k) exists
        int need = prefixSum - k;
        if (prefixMap.find(need) != prefixMap.end()) {
            int len = i - prefixMap[need];
            maxLen = max(maxLen, len);
        }
        
        // Store prefixSum only if not already present (keep earliest index)
        if (prefixMap.find(prefixSum) == prefixMap.end()) {
            prefixMap[prefixSum] = i;
        }
    }
    
    return maxLen;
}






/*
    =====================================================
    COUNT SUBARRAY SUM EQUALS K
    =====================================================

    Problem: Given an array of integers and an integer k, return the total 
    number of subarrays whose sum equals k.

    Video link : https://www.youtube.com/watch?v=xvNwoz-ufXA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=33

    Example:
    Input: nums = [1, 1, 1], k = 2
    Output: 2
    Explanation: Subarrays [1,1] (index 0-1) and [1,1] (index 1-2) have sum = 2

    Input: nums = [1, 2, 3], k = 3
    Output: 2
    Explanation: Subarrays [1,2] and [3] have sum = 3

    =====================================================
    INTUITION:
    =====================================================
    
    This is similar to "Longest Subarray with Sum K" but instead of 
    finding length, we COUNT all such subarrays.

    Key Difference from "Longest Subarray":
    - In "Longest", we stored EARLIEST index (to maximize length)
    - Here, we store COUNT of each prefix sum (to count all occurrences)

    If prefix[j] - prefix[i] = k, then subarray (i+1 to j) has sum = k.
    Rearranging: prefix[j] - k = prefix[i]

    For each prefix sum, we ask: "How many times have we seen (prefixSum - k)?"
    Each occurrence represents a valid subarray ending at current index.

    =====================================================
    APPROACH:
    =====================================================
    1. Initialize prefixSum = 0, count = 0
    2. Create hashmap: {prefixSum → frequency}
    3. IMPORTANT: Initialize map[0] = 1 (empty prefix has sum 0)
    4. For each element:
       a. prefixSum += arr[i]
       b. If (prefixSum - k) exists in map → count += map[prefixSum - k]
       c. Increment map[prefixSum]
    5. Return count

    Why map[0] = 1?
    - If prefixSum itself equals k, we need (prefixSum - k = 0) to exist
    - This represents a subarray from index 0 to current index

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: nums = [1, 2, 3, -3, 1, 1, 1, 4, 2, -3], k = 3

    Initialize: prefixSum = 0, count = 0, map = {0: 1}

    i=0, num=1:
        prefixSum = 1
        need = 1 - 3 = -2 (not in map) → count = 0
        map = {0:1, 1:1}

    i=1, num=2:
        prefixSum = 3
        need = 3 - 3 = 0 (in map, freq=1) → count = 0 + 1 = 1
        map = {0:1, 1:1, 3:1}
        ✓ Found: [1,2] = 3

    i=2, num=3:
        prefixSum = 6
        need = 6 - 3 = 3 (in map, freq=1) → count = 1 + 1 = 2
        map = {0:1, 1:1, 3:1, 6:1}
        ✓ Found: [3] = 3

    i=3, num=-3:
        prefixSum = 3
        need = 3 - 3 = 0 (in map, freq=1) → count = 2 + 1 = 3
        map = {0:1, 1:1, 3:2, 6:1}
        ✓ Found: [1,2,3,-3] = 3

    i=4, num=1:
        prefixSum = 4
        need = 4 - 3 = 1 (in map, freq=1) → count = 3 + 1 = 4
        map = {0:1, 1:1, 3:2, 6:1, 4:1}
        ✓ Found: [2,3,-3,1] = 3

    i=5, num=1:
        prefixSum = 5
        need = 5 - 3 = 2 (not in map) → count = 4
        map = {0:1, 1:1, 3:2, 6:1, 4:1, 5:1}

    i=6, num=1:
        prefixSum = 6
        need = 6 - 3 = 3 (in map, freq=2) → count = 4 + 2 = 6
        map = {0:1, 1:1, 3:2, 6:2, 4:1, 5:1}
        ✓ Found: [3,-3,1,1,1] and [-3,1,1,1] = 3 each (2 subarrays!)

    i=7, num=4:
        prefixSum = 10
        need = 10 - 3 = 7 (not in map) → count = 6
        map = {0:1, 1:1, 3:2, 6:2, 4:1, 5:1, 10:1}

    i=8, num=2:
        prefixSum = 12
        need = 12 - 3 = 9 (not in map) → count = 6
        map = {0:1, 1:1, 3:2, 6:2, 4:1, 5:1, 10:1, 12:1}

    i=9, num=-3:
        prefixSum = 9
        need = 9 - 3 = 6 (in map, freq=2) → count = 6 + 2 = 8
        map = {0:1, 1:1, 3:2, 6:2, 4:1, 5:1, 10:1, 12:1, 9:1}
        ✓ Found: [1,1,1,4,2,-3] and [1,1,4,2,-3] = 3 each (2 subarrays!)

    Output: 8 ✓
    
    All 8 subarrays with sum = 3:
    1. [1, 2]
    2. [3]
    3. [1, 2, 3, -3]
    4. [2, 3, -3, 1]
    5. [3, -3, 1, 1, 1]
    6. [-3, 1, 1, 1]
    7. [1, 1, 1, 4, 2, -3]
    8. [1, 1, 4, 2, -3]

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass
    SPACE COMPLEXITY: O(n) - HashMap storage
    =====================================================
*/

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;  // {prefixSum: frequency (how many times this prefixSum has occurred)}
    prefixCount[0] = 1;  // Empty prefix with sum 0
    
    int prefixSum = 0;  // prefixSum = sum of all elements from start to current index
    int count = 0;  // count = number of subarrays with sum = k
    
    for (int num : nums) {
        prefixSum += num;   // Add current element to prefixSum
        
        // Check how many times (prefixSum - k) occurred
        int need = prefixSum - k;
        if (prefixCount.find(need) != prefixCount.end()) {  // We can also write as prefixCount.count(need) > 0
            count += prefixCount[need];
        }
        
        // Add current prefixSum to map
        prefixCount[prefixSum]++;
    }
    
    return count;
}



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