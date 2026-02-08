/*
    =====================================================
    FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY
    =====================================================

    Problem: Given a sorted array of integers and a target value, find the 
    starting and ending position of the target. If the target is not found, 
    return [-1, -1]. Must run in O(log n) time.

    Example:
    Input: nums = [5, 7, 7, 8, 8, 10], target = 8
    Output: [3, 4]

    Input: nums = [5, 7, 7, 8, 8, 10], target = 6
    Output: [-1, -1]

    Input: nums = [1], target = 1
    Output: [0, 0]

    =====================================================
    INTUITION:
    =====================================================
    
    Linear scan would be O(n) — too slow. Since the array is SORTED, 
    we use BINARY SEARCH.

    But standard binary search finds ANY occurrence. We need the FIRST 
    and LAST occurrence. So we modify binary search twice:

    1. Lower Bound (First Occurrence):
       - When we find target, DON'T stop — keep searching LEFT (right = mid - 1)
       - This pushes us towards the first occurrence
       - Store the answer each time we find target

    2. Upper Bound (Last Occurrence):
       - When we find target, DON'T stop — keep searching RIGHT (left = mid + 1)
       - This pushes us towards the last occurrence
       - Store the answer each time we find target

    Why does this work?
    - In normal binary search, we return immediately on finding target
    - Here, even after finding target, we continue searching in ONE direction
    - This narrows down to the boundary (first or last) occurrence

    =====================================================
    APPROACH:
    =====================================================
    1. Run modified binary search to find FIRST position:
       - If nums[mid] == target → store mid as answer, search LEFT (right = mid - 1)
       - If nums[mid] < target → search RIGHT (left = mid + 1)
       - If nums[mid] > target → search LEFT (right = mid - 1)
    2. Run modified binary search to find LAST position:
       - If nums[mid] == target → store mid as answer, search RIGHT (left = mid + 1)
       - If nums[mid] < target → search RIGHT (left = mid + 1)
       - If nums[mid] > target → search LEFT (right = mid - 1)
    3. Return {first, last}

    =====================================================
    EXAMPLE DRY RUN (Finding FIRST occurrence):
    =====================================================
    Input: nums = [5, 7, 7, 8, 8, 10], target = 8

    left=0, right=5, ans=-1

    Iteration 1:
        mid = 2, nums[2] = 7
        7 < 8 → left = 3
    
    Iteration 2:
        mid = 4, nums[4] = 8
        8 == 8 → ans = 4, right = 3 (search LEFT for earlier occurrence)
    
    Iteration 3:
        mid = 3, nums[3] = 8
        8 == 8 → ans = 3, right = 2 (search LEFT)
    
    left(3) > right(2) → stop
    First position = 3 ✓

    =====================================================
    EXAMPLE DRY RUN (Finding LAST occurrence):
    =====================================================
    Input: nums = [5, 7, 7, 8, 8, 10], target = 8

    left=0, right=5, ans=-1

    Iteration 1:
        mid = 2, nums[2] = 7
        7 < 8 → left = 3
    
    Iteration 2:
        mid = 4, nums[4] = 8
        8 == 8 → ans = 4, left = 5 (search RIGHT for later occurrence)
    
    Iteration 3:
        mid = 5, nums[5] = 10
        10 > 8 → right = 4
    
    left(5) > right(4) → stop
    Last position = 4 ✓

    Output: [3, 4] ✓

    =====================================================
    TIME COMPLEXITY:  O(log n) - Two binary searches = O(2 log n) = O(log n)
    SPACE COMPLEXITY: O(1) - Only using variables
    =====================================================
*/

#include <iostream>
#include <vector>
using namespace std;

int findFirst(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int ans = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            ans = mid;
            right = mid - 1;  // Keep searching LEFT for earlier occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return ans;
}

int findLast(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int ans = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            ans = mid;
            left = mid + 1;  // Keep searching RIGHT for later occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return ans;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = findFirst(nums, target);
    int last = findLast(nums, target);
    return {first, last};
}
