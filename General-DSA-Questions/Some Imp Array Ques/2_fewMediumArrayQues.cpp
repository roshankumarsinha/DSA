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

int main() {
    cout << "--- LONGEST SUBARRAY WITH SUM K ---\n\n";
    
    // Test case 1
    vector<int> arr1 = {1, -1, 5, -2, 3};
    int k1 = 3;
    cout << "Array: [1, -1, 5, -2, 3], k = " << k1 << endl;
    cout << "Longest Subarray Length: " << longestSubarrayWithSumK(arr1, k1) << endl;
    
    // Test case 2
    vector<int> arr2 = {2, 0, 0, 3};
    int k2 = 3;
    cout << "\nArray: [2, 0, 0, 3], k = " << k2 << endl;
    cout << "Longest Subarray Length: " << longestSubarrayWithSumK(arr2, k2) << endl;
    
    // Test case 3 (with negatives)
    vector<int> arr3 = {-1, 1, 1};
    int k3 = 1;
    cout << "\nArray: [-1, 1, 1], k = " << k3 << endl;
    cout << "Longest Subarray Length: " << longestSubarrayWithSumK(arr3, k3) << endl;
    
    return 0;
}
