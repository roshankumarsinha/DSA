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
    3. IMPORTANT: Initialize map[0] = -1 (empty prefix has sum 0)
    3. For each index i:
       a. prefixSum += arr[i]
       c. If (prefixSum - k) in map → maxLen = max(maxLen, i - map[prefixSum-k])
       d. If prefixSum NOT in map → store {prefixSum: i}
    4. Return maxLen

    Why map[0] = -1?
    - If prefixSum itself equals k, we need (prefixSum - k = 0) to exist
    - This represents a subarray from index 0 to current index

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: arr = [1, -1, 5, -2, 3], k = 3, map={0:-1}

    i=0: prefixSum=1, need=-2 (not found), map={0:-1, 1:0}
    i=1: prefixSum=0, need=-3 (not found), map={0:-1, 1:0, 0:1}
    i=2: prefixSum=5, need=2 (not found), map={0:-1, 1:0, 0:1, 5:2}
    i=3: prefixSum=3, need=0, (found at -1) → len=3-(-1)=4, maxLen=4, map={0:-1, 1:0, 0:1, 5:2, 3:3}
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
    prefixMap[0] = -1;   // IMPORTANT: Empty Prefix with sum o
    int prefixSum = 0;
    int maxLen = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        prefixSum += arr[i];
        
        // Case : Check if (prefixSum - k) exists
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
    COUNT SUBARRAYS WITH EQUAL 0s AND 1s
    =====================================================

    Problem: Given an array arr[] of size n containing only 0s and 1s,
    count the number of subarrays having equal number of 0s and 1s.

    Example:
    Input: arr = [1, 0, 0, 1, 0, 1, 1]
    Output: 8

    Input: arr = [1, 0, 1, 0]
    Output: 4
    Explanation: Subarrays [1,0], [0,1], [1,0,1,0], [0,1,0,1]

    =====================================================
    INTUITION:
    =====================================================
    
    This problem is a clever transformation of "Count Subarrays with Sum K"!

    Key Trick: Replace every 0 with -1.
    
    Why? If a subarray has equal 0s and 1s:
    - After replacing 0 → -1, each pair (one 1 and one -1) cancels out
    - So the subarray sum becomes 0!
    
    Example: [1, 0, 0, 1] → [1, -1, -1, 1]
    Sum = 1 + (-1) + (-1) + 1 = 0 ✓ (equal 0s and 1s)

    So the problem reduces to:
    "Count subarrays with sum = 0" after replacing 0s with -1s.

    This is exactly the PREFIX SUM + HASHMAP pattern we already know!

    If prefix[j] - prefix[i] = 0
    Then prefix[j] = prefix[i]
    
    So we just need to count how many times the same prefix sum 
    has appeared before!

    =====================================================
    APPROACH:
    =====================================================
    1. Replace all 0s with -1s (or treat 0 as -1 during computation)
    2. Initialize prefixSum = 0, count = 0
    3. Create hashmap: {prefixSum → frequency}
    4. IMPORTANT: Initialize map[0] = 1 (empty prefix has sum 0)
    5. For each element:
       a. prefixSum += (arr[i] == 0 ? -1 : 1)
       b. If prefixSum exists in map → count += map[prefixSum]
       c. Increment map[prefixSum]
    6. Return count

    Why map[0] = 1?
    - If prefixSum becomes 0, the subarray from index 0 to current index
      has equal 0s and 1s. We need to count this case.

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: arr = [1, 0, 0, 1, 0, 1, 1]
    After replacing 0 → -1: [1, -1, -1, 1, -1, 1, 1]

    Initialize: prefixSum = 0, count = 0, map = {0: 1}

    i=0, num=1:
        prefixSum = 1
        1 not in map → count = 0
        map = {0:1, 1:1}

    i=1, num=-1:
        prefixSum = 0
        0 in map (freq=1) → count = 0 + 1 = 1
        map = {0:2, 1:1}
        ✓ Found: [1,0]

    i=2, num=-1:
        prefixSum = -1
        -1 not in map → count = 1
        map = {0:2, 1:1, -1:1}

    i=3, num=1:
        prefixSum = 0
        0 in map (freq=2) → count = 1 + 2 = 3
        map = {0:3, 1:1, -1:1}
        ✓ Found: [0,1] and [1,0,0,1]

    i=4, num=-1:
        prefixSum = -1
        -1 in map (freq=1) → count = 3 + 1 = 4
        map = {0:3, 1:1, -1:2}
        ✓ Found: [1,0]

    i=5, num=1:
        prefixSum = 0
        0 in map (freq=3) → count = 4 + 3 = 7
        map = {0:4, 1:1, -1:2}
        ✓ Found: [0,1], [0,1,0,1], [1,0,0,1,0,1]

    i=6, num=1:
        prefixSum = 1
        1 in map (freq=1) → count = 7 + 1 = 8
        map = {0:4, 1:2, -1:2}
        ✓ Found: [0,0,1,0,1,1]

    Output: 8 ✓

    All 8 subarrays with equal 0s and 1s:
    1. [1, 0]              (index 0-1)
    2. [0, 1]              (index 2-3)
    3. [1, 0, 0, 1]        (index 0-3)
    4. [1, 0]              (index 3-4)
    5. [0, 1]              (index 4-5)
    6. [0, 1, 0, 1]        (index 2-5)
    7. [1, 0, 0, 1, 0, 1]  (index 0-5)
    8. [0, 0, 1, 0, 1, 1]  (index 1-6)

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass
    SPACE COMPLEXITY: O(n) - HashMap storage
    =====================================================
*/

int countSubarraysWithEqual0sAnd1s(vector<int>& arr) {
    unordered_map<int, int> prefixCount;  // {prefixSum: frequency}
    prefixCount[0] = 1;  // IMPORTANT: Empty prefix with sum 0
    int prefixSum = 0;
    int count = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        // Treat 0 as -1
        prefixSum += (arr[i] == 0) ? -1 : 1;
        
        // If this prefixSum was seen before, all previous occurrences
        // form valid subarrays ending at current index
        if (prefixCount.find(prefixSum) != prefixCount.end()) {
            count += prefixCount[prefixSum];
        }
        
        // Add current prefixSum to map
        prefixCount[prefixSum]++;
    }
    
    return count;
}




/*
    =====================================================
    Longest Subarray with Equal 0s and 1s
    =====================================================  

    Simillarly we have one more question to find longest subarray with equal 0s and 1s, which is similar to
    longest subarray with sum k, where we will treat 0 as -1 and 1 as +1, and then we will find longest subarray with sum = 0.
*/
