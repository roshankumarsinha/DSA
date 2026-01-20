/*
    =====================================================
    REMOVE DUPLICATES IN-PLACE FROM SORTED ARRAY
    =====================================================

    Problem: Given a sorted array, remove the duplicates in-place such that each element appears only once and return the new length.

    =====================================================
    INTUITION:
    =====================================================
    Since the array is SORTED, all duplicate elements are ADJACENT to each other.
    
    We can use the TWO-POINTER technique:
    - One pointer (i) to track the position where the next unique element should go
    - Another pointer (j) to scan through the array

    Key Insight: We only need to compare adjacent elements. If they're different,
    we've found a new unique element.

    =====================================================
    APPROACH:
    =====================================================
    1. Use pointer 'i' starting at index 0 (first unique element position)
    2. Use pointer 'j' to iterate from index 1 to end
    3. If arr[j] != arr[i], we found a new unique element:
       - Increment i
       - Place arr[j] at position i
    4. Return i + 1 (length of unique elements)

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [1, 1, 2, 2, 2, 3, 3]
    
    Initial: i = 0, j = 1
    Array:   [1, 1, 2, 2, 2, 3, 3]
              i  j

    Step 1: arr[j]=1 == arr[i]=1 → Skip, j++
    Array:   [1, 1, 2, 2, 2, 3, 3]
              i     j

    Step 2: arr[j]=2 != arr[i]=1 → i++, arr[i]=arr[j]
    Array:   [1, 2, 2, 2, 2, 3, 3]
                 i  j

    Step 3: arr[j]=2 == arr[i]=2 → Skip, j++
    Array:   [1, 2, 2, 2, 2, 3, 3]
                 i     j

    Step 4: arr[j]=2 == arr[i]=2 → Skip, j++
    Array:   [1, 2, 2, 2, 2, 3, 3]
                 i        j

    Step 5: arr[j]=3 != arr[i]=2 → i++, arr[i]=arr[j]
    Array:   [1, 2, 3, 2, 2, 3, 3]
                    i        j

    Step 6: arr[j]=3 == arr[i]=3 → Skip, j++
    Array:   [1, 2, 3, 2, 2, 3, 3]
                    i           j

    Loop ends. Return i + 1 = 3
    
    Result: First 3 elements [1, 2, 3] are unique.

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through array
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    // Edge case: empty array
    if (nums.size() == 0) return 0;
    
    // 'i' points to the last unique element's position
    int i = 0;
    
    // 'j' scans through the array starting from index 1
    for (int j = 1; j < nums.size(); j++) {
        // If current element is different from the last unique element
        if (nums[j] != nums[i]) {
            i++;                // Move to next position for unique element
            nums[i] = nums[j];  // Place the new unique element
        }
    }
    
    // Return count of unique elements (i is index, so add 1)
    return i + 1;
}



/*
    =====================================================
    ROTATE ARRAY BY K ELEMENTS
    =====================================================

    Problem: Given an array of integers, rotate the array by k elements 
    either left or right.

    =====================================================
    INTUITION:
    =====================================================
    The key observation is that rotating an array can be achieved using 
    the REVERSAL ALGORITHM.

    For RIGHT ROTATION by k:
    - If we reverse the entire array, the last k elements come to front (but reversed)
    - Then reverse first k elements to fix their order
    - Then reverse remaining elements to fix their order

    For LEFT ROTATION by k:
    - Reverse first k elements
    - Reverse remaining n-k elements  
    - Reverse entire array

    Why this works?
    Think of it as: we're "folding" the array at position k.

    =====================================================
    APPROACH (Right Rotation):
    =====================================================
    1. Handle edge case: k = k % n (if k > n, we only need k % n rotations)
    2. Reverse the entire array
    3. Reverse the first k elements
    4. Reverse the remaining n-k elements

    =====================================================
    EXAMPLE DRY RUN (Right Rotation by k=3):
    =====================================================
    Input: [1, 2, 3, 4, 5, 6, 7], k = 3

    Step 1: k = 3 % 7 = 3

    Step 2: Reverse entire array
    [1, 2, 3, 4, 5, 6, 7] → [7, 6, 5, 4, 3, 2, 1]

    Step 3: Reverse first k=3 elements
    [7, 6, 5, 4, 3, 2, 1] → [5, 6, 7, 4, 3, 2, 1]
     ↑-----↑

    Step 4: Reverse remaining n-k=4 elements
    [5, 6, 7, 4, 3, 2, 1] → [5, 6, 7, 1, 2, 3, 4]
              ↑--------↑

    Output: [5, 6, 7, 1, 2, 3, 4] ✓

    =====================================================
    EXAMPLE DRY RUN (Left Rotation by k=2):
    =====================================================
    Input: [1, 2, 3, 4, 5], k = 2

    Step 1: Reverse first k=2 elements
    [1, 2, 3, 4, 5] → [2, 1, 3, 4, 5]
     ↑--↑

    Step 2: Reverse remaining n-k=3 elements
    [2, 1, 3, 4, 5] → [2, 1, 5, 4, 3]
           ↑-----↑

    Step 3: Reverse entire array
    [2, 1, 5, 4, 3] → [3, 4, 5, 1, 2]

    Output: [3, 4, 5, 1, 2] ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Each element is reversed twice at most
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

// Right Rotation by k elements (using STL reverse)
void rotateRight(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0) return;
    
    k = k % n;  // Handle k > n
    if (k == 0) return;
    
    // Step 1: Reverse entire array
    reverse(nums.begin(), nums.end());
    // Step 2: Reverse first k elements
    reverse(nums.begin(), nums.begin() + k);
    // Step 3: Reverse remaining n-k elements
    reverse(nums.begin() + k, nums.end());
}

// Left Rotation by k elements (using STL reverse)
void rotateLeft(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0) return;
    
    k = k % n;  // Handle k > n
    if (k == 0) return;
    
    // Step 1: Reverse first k elements
    reverse(nums.begin(), nums.begin() + k);
    // Step 2: Reverse remaining n-k elements
    reverse(nums.begin() + k, nums.end());
    // Step 3: Reverse entire array
    reverse(nums.begin(), nums.end());
}




/*
    =====================================================
    MOVE ALL ZEROS TO THE END OF ARRAY
    =====================================================

    Problem: Given an array of integers, move all zeros to the end while 
    maintaining the relative order of non-zero elements.

    =====================================================
    INTUITION:
    =====================================================
    We use the TWO-POINTER technique:
    - One pointer (i) tracks the position where the next non-zero element should go
    - Another pointer (j) scans through the array looking for non-zero elements

    Key Insight: Instead of "moving zeros to end", think of it as 
    "moving non-zeros to front" — zeros will naturally end up at the back.

    This is similar to the "Remove Duplicates" problem — we're essentially 
    partitioning the array into [non-zeros | zeros].

    =====================================================
    APPROACH:
    =====================================================
    1. Use pointer 'i' starting at 0 (position for next non-zero)
    2. Use pointer 'j' to iterate through the array
    3. If arr[j] is non-zero:
       - Swap arr[i] and arr[j]
       - Increment i
    4. After loop, all non-zeros are at front, zeros at end

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [0, 1, 0, 3, 12]

    Initial: i = 0, j = 0
    Array:   [0, 1, 0, 3, 12]
              i
              j

    Step 1: arr[j]=0 is zero → Skip, j++
    Array:   [0, 1, 0, 3, 12]
              i  j

    Step 2: arr[j]=1 != 0 → Swap arr[i] and arr[j], i++
    Array:   [1, 0, 0, 3, 12]
                 i  j

    Step 3: arr[j]=0 is zero → Skip, j++
    Array:   [1, 0, 0, 3, 12]
                 i     j

    Step 4: arr[j]=3 != 0 → Swap arr[i] and arr[j], i++
    Array:   [1, 3, 0, 0, 12]
                    i     j

    Step 5: arr[j]=12 != 0 → Swap arr[i] and arr[j], i++
    Array:   [1, 3, 12, 0, 0]
                        i     j (loop ends)

    Output: [1, 3, 12, 0, 0] ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through array
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/
void moveZeroes(vector<int>& nums) {
    int i = 0;  // Position for next non-zero element
    
    for (int j = 0; j < nums.size(); j++) {
        if (nums[j] != 0) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
}




/*
    =====================================================
    FIND THE MISSING NUMBER IN AN ARRAY
    =====================================================

    Problem: Given an integer N and an array of size N-1 containing N-1 
    numbers between 1 to N. Find the number (between 1 to N) that is 
    not present in the given array.

    =====================================================
    INTUITION:
    =====================================================
    
    Approach 1: SUM FORMULA
    - We know sum of 1 to N = N * (N + 1) / 2
    - If we subtract sum of array elements from this, we get missing number
    - Simple but can cause INTEGER OVERFLOW for large N

    Approach 2: XOR (Preferred)
    - XOR has special properties:
      * a ^ a = 0 (same numbers cancel out)
      * a ^ 0 = a (XOR with 0 gives same number)
      * XOR is associative and commutative
    - If we XOR all numbers from 1 to N AND all array elements:
      * All present numbers appear twice → cancel out to 0
      * Missing number appears once → remains as answer
    - NO OVERFLOW issues!

    =====================================================
    APPROACH (XOR Method):
    =====================================================
    1. Initialize xor1 = 0 (for XOR of 1 to N)
    2. Initialize xor2 = 0 (for XOR of array elements)
    3. XOR all numbers from 1 to N into xor1
    4. XOR all array elements into xor2
    5. Result = xor1 ^ xor2 (missing number)

    =====================================================
    EXAMPLE DRY RUN (XOR Method):
    =====================================================
    Input: N = 5, Array = [1, 2, 4, 5]
    Missing number is 3

    Step 1: XOR of 1 to N
    xor1 = 1 ^ 2 ^ 3 ^ 4 ^ 5

    Step 2: XOR of array elements
    xor2 = 1 ^ 2 ^ 4 ^ 5

    Step 3: xor1 ^ xor2
    = (1 ^ 2 ^ 3 ^ 4 ^ 5) ^ (1 ^ 2 ^ 4 ^ 5)
    = 1^1 ^ 2^2 ^ 3 ^ 4^4 ^ 5^5    (rearranging)
    =  0  ^  0  ^ 3 ^  0  ^  0
    = 3 ✓

    =====================================================
    EXAMPLE DRY RUN (Sum Method):
    =====================================================
    Input: N = 5, Array = [1, 2, 4, 5]

    Expected Sum = 5 * 6 / 2 = 15
    Actual Sum = 1 + 2 + 4 + 5 = 12
    Missing = 15 - 12 = 3 ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through array
    SPACE COMPLEXITY: O(1) - Only using variables
    =====================================================
*/

// Method 1: Using Sum Formula (Can overflow for large N)
int missingNumberSum(vector<int>& nums, int n) {
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    
    for (int num : nums) {
        actualSum += num;
    }
    
    return expectedSum - actualSum;
}

// Method 2: Using XOR (Preferred - No overflow)
int missingNumberXOR(vector<int>& nums, int n) {
    int xor1 = 0;  // XOR of 1 to N
    int xor2 = 0;  // XOR of array elements
    
    // XOR all numbers from 1 to N
    for (int i = 1; i <= n; i++) {
        xor1 ^= i;
    }
    
    // XOR all array elements
    for (int num : nums) {
        xor2 ^= num;
    }
    
    // Missing number = xor1 ^ xor2
    return xor1 ^ xor2;
}
