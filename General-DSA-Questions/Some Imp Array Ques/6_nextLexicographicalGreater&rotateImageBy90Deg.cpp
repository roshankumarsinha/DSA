/*
    =====================================================
    NEXT PERMUTATION - Find Next Lexicographically Greater Permutation
    =====================================================

    Problem: Given an array of integers, rearrange the numbers into the 
    lexicographically next greater permutation.
    If not possible, rearrange to the lowest order (sorted ascending).

    Example:
    Input:  [1, 2, 3] → Output: [1, 3, 2]
    Input:  [3, 2, 1] → Output: [1, 2, 3] (no greater, reset to smallest)
    Input:  [1, 3, 2] → Output: [2, 1, 3]
    Input:  [2, 1, 5, 4, 3, 0, 0] → Output: [2, 3, 0, 0, 1, 4, 5]

    =====================================================
    INTUITION:
    =====================================================
    
    To find the NEXT greater permutation, we need to:
    1. Find the rightmost element that can be increased (break point)
    2. Increase it by the smallest possible amount
    3. Make the suffix as small as possible
    
    Key Observations:
    - If array is in descending order → no next permutation (reset)
    - We look from RIGHT to LEFT for the first "dip" (arr[i] < arr[i+1])
    - This is called the "break point"
    
    Example: [2, 1, 5, 4, 3, 0, 0]
                 ↑
              break point (1 < 5)
    
    After break point, elements are in descending order.
    We swap break point with the smallest element greater than it (from right).
    Then reverse the suffix to get smallest arrangement.

    =====================================================
    APPROACH:
    =====================================================
    1. Find break point: Traverse from right, find first i where arr[i] < arr[i+1]
    2. If no break point found → array is largest permutation → reverse entire array
    3. Find swap candidate: From right, find first element > arr[breakPoint]
    4. Swap arr[breakPoint] with swap candidate
    5. Reverse the suffix (elements after break point)

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [2, 1, 5, 4, 3, 0, 0]
           [0  1  2  3  4  5  6]  ← indices

    Step 1: Find break point (from right, find arr[i] < arr[i+1])
            i=5: arr[5]=0, arr[6]=0 → 0 < 0? NO
            i=4: arr[4]=3, arr[5]=0 → 3 < 0? NO
            i=3: arr[3]=4, arr[4]=3 → 4 < 3? NO
            i=2: arr[2]=5, arr[3]=4 → 5 < 4? NO
            i=1: arr[1]=1, arr[2]=5 → 1 < 5? YES ✓
            Break point = 1

    Step 2: Find swap candidate (from right, first element > arr[1]=1)
            j=6: arr[6]=0 → 0 > 1? NO
            j=5: arr[5]=0 → 0 > 1? NO
            j=4: arr[4]=3 → 3 > 1? YES ✓
            Swap candidate = 4

    Step 3: Swap arr[1] and arr[4]
            [2, 1, 5, 4, 3, 0, 0] → [2, 3, 5, 4, 1, 0, 0]
                ↑        ↑

    Step 4: Reverse suffix (from index 2 to end)
            [2, 3, 5, 4, 1, 0, 0] → [2, 3, 0, 0, 1, 4, 5]
                   └──────────┘ reversed

    Output: [2, 3, 0, 0, 1, 4, 5] ✓

    =====================================================
    WHY REVERSE THE SUFFIX?
    =====================================================
    After the break point, elements are in DESCENDING order.
    To get the smallest arrangement, we need ASCENDING order.
    Reversing a descending sequence gives ascending order!

    =====================================================
    TIME COMPLEXITY:  O(n) - At most 3 passes
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

#include <iostream>
#include <vector>
using namespace std;

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int breakPoint = -1;
    
    // Step 1: Find break point (rightmost i where nums[i] < nums[i+1])
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            breakPoint = i;
            break;
        }
    }
    
    // Step 2: If no break point, reverse entire array (largest → smallest)
    if (breakPoint == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }
    
    // Step 3: Find swap candidate (rightmost element > nums[breakPoint])
    for (int j = n - 1; j > breakPoint; j--) {
        if (nums[j] > nums[breakPoint]) {
            swap(nums[breakPoint], nums[j]);
            break;
        }
    }
    
    // Step 4: Reverse suffix (elements after break point)
    reverse(nums.begin() + breakPoint + 1, nums.end());
}



/*
    =====================================================
    ROTATE IMAGE BY 90 DEGREES (Clockwise)
    =====================================================

    Problem: Given an N x N 2D matrix, rotate the matrix by 90 degrees 
    clockwise. The rotation must be done IN-PLACE.

    Example:
    Input:              Output:
    1  2  3             7  4  1
    4  5  6     →       8  5  2
    7  8  9             9  6  3

    =====================================================
    INTUITION:
    =====================================================
    
    Observation: What happens when we rotate 90° clockwise?
    
    Original position (i, j) → New position (j, n-1-i)
    
    For a 3x3 matrix:
    (0,0) → (0,2)    (0,1) → (1,2)    (0,2) → (2,2)
    (1,0) → (0,1)    (1,1) → (1,1)    (1,2) → (2,1)
    (2,0) → (0,0)    (2,1) → (1,0)    (2,2) → (2,0)
    
    Key Insight: 90° clockwise rotation = TRANSPOSE + REVERSE each row
    
    Why does this work?
    - Transpose: (i, j) → (j, i)
    - Reverse row: (j, i) → (j, n-1-i)
    - Combined: (i, j) → (j, n-1-i) ✓ (matches rotation formula!)

    =====================================================
    APPROACH:
    =====================================================
    Step 1: TRANSPOSE the matrix (swap rows and columns)
            - Swap matrix[i][j] with matrix[j][i] for i < j
    
    Step 2: REVERSE each row
            - For each row, swap elements from both ends

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input:
    1  2  3
    4  5  6
    7  8  9

    Step 1: TRANSPOSE (swap across diagonal)
    
    Swap (0,1)↔(1,0): 2↔4
    Swap (0,2)↔(2,0): 3↔7
    Swap (1,2)↔(2,1): 6↔8

    After Transpose:
    1  4  7
    2  5  8
    3  6  9

    Step 2: REVERSE each row

    Row 0: [1, 4, 7] → [7, 4, 1]
    Row 1: [2, 5, 8] → [8, 5, 2]
    Row 2: [3, 6, 9] → [9, 6, 3]

    Final Output:
    7  4  1
    8  5  2
    9  6  3  ✓

    =====================================================
    ROTATION VARIANTS:
    =====================================================
    
    90° Clockwise:        Transpose → Reverse each ROW
    90° Anti-clockwise:   Transpose → Reverse each COLUMN
    180°:                 Reverse each ROW → Reverse each COLUMN
                      OR  Rotate 90° twice

    =====================================================
    TIME COMPLEXITY:  O(n²) - Visit each element twice
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

void rotate90Clockwise(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Step 1: Transpose the matrix
    // Only iterate upper triangle (i < j) to avoid double swapping
    for (int i = 0; i < n; i++) {   // Traverse rows
        for (int j = i + 1; j < n; j++) {   // Traverse columns, with j starting from i+1, because we are only swapping upper triangle
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Step 2: Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}