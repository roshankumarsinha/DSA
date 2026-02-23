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

#include <vector>
using namespace std;
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
