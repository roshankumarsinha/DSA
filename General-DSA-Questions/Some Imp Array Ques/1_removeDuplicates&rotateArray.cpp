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
