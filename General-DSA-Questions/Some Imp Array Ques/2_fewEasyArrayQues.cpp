/*
    =====================================================
    COUNT NUMBER OF VALID SPLITS IN AN ARRAY
    =====================================================

    Problem: Given a 0-indexed integer array nums of length n, count the 
    number of valid splits where:
    1. The sum of the first (i + 1) elements >= sum of the remaining elements.
    2. There must be at least one element on the right side (i.e., i < n - 1).

    Example:
    Input: nums = [10, 4, -8, 7]
    Output: 2
    Explanation:
    Split at i=0: left=[10], right=[4,-8,7] → 10 >= 3 ✓
    Split at i=1: left=[10,4], right=[-8,7] → 14 >= -1 ✓
    Split at i=2: left=[10,4,-8], right=[7] → 6 >= 7 ✗

    Input: nums = [2, 3, 1, 0]
    Output: 2

    =====================================================
    INTUITION:
    =====================================================
    
    Brute Force: For each split point, calculate left sum and right sum 
    separately → O(n²). Too slow!

    Optimal: Use PREFIX SUM approach.

    Key Observation:
    - totalSum = leftSum + rightSum
    - So rightSum = totalSum - leftSum
    - Condition: leftSum >= rightSum
    - Which means: leftSum >= totalSum - leftSum
    - Simplified: 2 * leftSum >= totalSum

    So we just need to:
    1. Compute totalSum once
    2. Maintain a running leftSum
    3. Check if 2 * leftSum >= totalSum at each valid split point

    =====================================================
    APPROACH:
    =====================================================
    1. Compute totalSum of the array
    2. Initialize leftSum = 0, count = 0
    3. For i from 0 to n-2 (at least one element must remain on right):
       a. leftSum += nums[i]
       b. rightSum = totalSum - leftSum
       c. If leftSum >= rightSum → count++
    4. Return count

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: nums = [10, 4, -8, 7]
    totalSum = 10 + 4 + (-8) + 7 = 13

    Initialize: leftSum = 0, count = 0

    i=0:
        leftSum = 10
        rightSum = 13 - 10 = 3
        10 >= 3 → ✓ count = 1

    i=1:
        leftSum = 14
        rightSum = 13 - 14 = -1
        14 >= -1 → ✓ count = 2

    i=2:
        leftSum = 6
        rightSum = 13 - 6 = 7
        6 >= 7 → ✗ count = 2

    (i=3 is skipped, need at least one element on right)

    Output: 2 ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Two passes (one for totalSum, one for splits)
    SPACE COMPLEXITY: O(1) - Only using variables
    =====================================================
*/

#include <iostream>
#include <vector>
using namespace std;

int waysToSplitArray(vector<int>& nums) {
    int n = nums.size();
    
    long long totalSum = 0;
    for (int num : nums) {
        totalSum += num;
    }
    
    long long leftSum = 0;
    int count = 0;
    
    for (int i = 0; i < n - 1; i++) {
        leftSum += nums[i];
        long long rightSum = totalSum - leftSum;
        
        if (leftSum >= rightSum) {
            count++;
        }
    }
    
    return count;
}




/*
    =====================================================
    MINIMUM INCREMENT OPERATIONS TO MAKE ARRAY UNIQUE
    =====================================================

    Problem: Given an array arr[] of integers. In one operation you can 
    choose an index i and increment arr[i] by 1. Return the minimum number 
    of operations needed to make every value in the array unique.

    Example:
    Input: arr = [1, 1, 2, 3]
    Output: 3
    Explanation: 
    arr[0]=1 stays, arr[1]=1→4 (3 ops). Result: [1, 2, 3, 4]
    Total operations = 3

    Input: arr = [3, 2, 1, 2, 1, 7]
    Output: 6
    Explanation: After sorting [1, 1, 2, 2, 3, 7] → [1, 2, 3, 4, 5, 7]
    Operations = (2-1) + (3-2) + (4-2) + (5-3) = 1 + 1 + 2 + 2 = 6

    =====================================================
    INTUITION 1:
    =====================================================
    
    Key Insight: We can only INCREMENT, never decrement. So smaller 
    duplicates should stay, and larger duplicates must be pushed forward.

    If we SORT the array first, duplicates become adjacent. Then for 
    each element, if it's not greater than the previous element, we 
    must increment it to (previous + 1).

    Why sorting works?
    - After sorting, we process elements left to right
    - Each element must be at least (previous element + 1)
    - The difference tells us how many increments we need
    - This greedy approach gives minimum operations because we 
      push each duplicate to the nearest available value

    =====================================================
    APPROACH 1: SORTING
    =====================================================
    1. Sort the array
    2. Initialize operations = 0
    3. For i from 1 to n-1:
       a. If arr[i] <= arr[i-1]:
          - needed = arr[i-1] + 1
          - operations += needed - arr[i]
          - arr[i] = needed
    4. Return operations

    =====================================================
    EXAMPLE DRY RUN :
    =====================================================
    Input: arr = [1, 1, 2, 3]
    Already sorted: [1, 1, 2, 3]

    Initialize: operations = 0

    i=1: arr[1]=1 <= arr[0]=1
        needed = 2, operations += 2 - 1 = 1, operations = 1
        arr[1] = 2 → [1, 2, 2, 3]

    i=2: arr[2]=2 <= arr[1]=2
        needed = 3, operations += 3 - 2 = 1, operations = 2
        arr[2] = 3 → [1, 2, 3, 3]

    i=3: arr[3]=3 <= arr[2]=3
        needed = 4, operations += 4 - 3 = 1, operations = 3
        arr[3] = 4 → [1, 2, 3, 4]

    Output: 3 ✓

    =====================================================
    TIME COMPLEXITY:  O(n log n) - Sorting dominates
    SPACE COMPLEXITY: O(1) - In-place (ignoring sort's internal space)
    =====================================================



    Instead of sorting (O(n log n)), we use a frequency array to 
    achieve O(n + maxVal) time.

    =====================================================
    INTUITION 2:
    =====================================================
    
    1. Build a frequency array: freq[x] = how many times x appears
    2. Sweep from 0 to maxVal + n:
       - If freq[i] > 1, there are (freq[i] - 1) duplicates at value i
       - Push those duplicates to i+1 (each push = 1 operation per element)
       - So: operations += (freq[i] - 1), and freq[i+1] += (freq[i] - 1)
    3. Each duplicate gets incremented by exactly 1 at each step, 
       cascading forward until it finds a free slot.

    Why maxVal + n?
    - Worst case: all elements are the same value (e.g., [5,5,5,5,5])
    - They cascade to [5,6,7,8,9], needing n-1 extra slots beyond max

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: arr = [3, 2, 1, 2, 1, 7]
    
    Step 1: Find maxVal = 7, create freq array of size 7 + 6 = 13

    Step 2: Build frequency array
    freq[1]=2, freq[2]=2, freq[3]=1, freq[7]=1

    Step 3: Sweep through freq array

    i=1: freq[1]=2, duplicates = 2-1 = 1
        operations += 1, operations = 1
        freq[2] += 1 → freq[2] = 3

    i=2: freq[2]=3, duplicates = 3-1 = 2
        operations += 2, operations = 3
        freq[3] += 2 → freq[3] = 3

    i=3: freq[3]=3, duplicates = 3-1 = 2
        operations += 2, operations = 5
        freq[4] += 2 → freq[4] = 2

    i=4: freq[4]=2, duplicates = 2-1 = 1
        operations += 1, operations = 6
        freq[5] += 1 → freq[5] = 1

    i=5: freq[5]=1 → no duplicates, skip
    i=6: freq[6]=0 → skip
    i=7: freq[7]=1 → no duplicates, skip

    Output: 6 ✓

    =====================================================
    TIME COMPLEXITY:  O(n + maxVal) - Build freq + single sweep
    SPACE COMPLEXITY: O(n + maxVal) - Frequency array
    =====================================================
*/

// Method 1: Sorting Approach - O(n log n) time, O(1) space
int minIncrementForUnique_Sort(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    
    int operations = 0;
    
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] <= arr[i - 1]) {
            int needed = arr[i - 1] + 1;
            operations += needed - arr[i];
            arr[i] = needed;
        }
    }
    
    return operations;
}


// Method 2: Counting Approach - O(n + maxVal) time, O(n + maxVal) space
int minIncrementForUnique(vector<int>& arr) {
    // Find maxVal to size frequency array
    unordered_map<int, int> freqMap;
    int maxVal = 0;     // To track maximum value in arr

    for (int num : arr) {
        freqMap[num]++;
        maxVal = max(maxVal, num);
    }

    int operations = 0;
    // Fixed upper bound: maxVal + n covers worst case (all elements same value)
    for (int i = 0; i < maxVal + (int)arr.size(); i++) {
        if (freqMap.count(i) && freqMap[i] > 1) {
            int duplicates = freqMap[i] - 1;    // Number of duplicates at value i
            operations += duplicates;   // Each duplicate needs 1 operation to move to next value
            freqMap[i + 1] += duplicates;  // Push duplicates to next value
        }
    }
    return operations;
    
}
