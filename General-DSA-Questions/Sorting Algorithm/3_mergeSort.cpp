// Write code to sort an array using merge sort.

// Merge Sort is a divide-and-conquer algorithm that sorts an array by recursively dividing it into halves, sorting each half, and then merging the sorted halves back together.

// Video link : https://www.youtube.com/watch?v=ogjf7ORKfd8
// Notes : https://takeuforward.org/data-structure/merge-sort-algorithm/

// Intuition: 
// 1. Merge Sort is a divide and conquers algorithm, it divides the given array into equal parts and then merges the 2 sorted parts. 
// 2. There are 2 main functions :
//    a.  merge(): This function is used to merge the 2 halves of the array. It assumes that both parts of the array are sorted and merges both of them.
//    b.  mergeSort(): This function divides the array into 2 parts. left to mid and mid+1 to right where,
//        left = leftmost index of the array
//        right = rightmost index of the array
//        mid = Middle index of the array 
// 3. We recursively split the array, and go from top-down until all sub-arrays size becomes 1.


// Approach:
// 1. mergeSort(arr[], left, right):
//    a.  In order to implement merge sort we need to first divide the given array into two halves.
//        Now, if we carefully observe, we need not divide the array and create a separate array, but we will divide the array's range into halves every time.
//        For example, the given range of the array is 0 to 4(0-based indexing). Now on the first go, we will divide the range into half like (0+4)/2 = 2.
//        So, the range of the left half will be 0 to 2 and for the right half, the range will be 3 to 4.
//        Similarly, if the given range is left to right, the range for the two halves will be left to mid and mid+1 to right, where mid = (left+right)/2.
//        This process will continue until the range size becomes 1.
//    b.  So, in mergeSort(), we will divide the array around the middle index(rather than creating a separate array) by making the recursive call :
//        1. mergeSort(arr,left,mid)   [Left half of the array]
//        2. mergeSort(arr,mid+1,right)  [Right half of the array]
//           where left = leftmost index of the array, right = rightmost index of the array, and mid = middle index of the array.
//    c.  Now, in order to complete the recursive function, we need to write the base case as well. We know from step 2.1, that our recursion ends when the array has only 1 element left.
//        So, the leftmost index, left, and the rightmost index right become the same as they are pointing to a single element.
//        Base Case: if(left >= right) return;
// 2. merge(arr[], left, mid, right):
//    a.  In the merge function, we will use a temp array to store the elements of the two sorted arrays after merging.
//        Here, the range of the left array is left to mid and the range for the right half is mid+1 to right.
//    b.  Now we will take two pointers left and right, where left starts from low and right starts from mid+1.
//    c.  Using a while loop( while(i <= mid && j <= right)), we will select two elements, one from each half, and will consider the smallest one among the two.
//        Then, we will insert the smallest element in the temp array.
//    d.  After that, the left-out elements in both halves will be copied as it is into the temp array.
//    e.  Now, we will just transfer the elements of the temp array to the range left to right in the original array.

#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted halves into a single sorted array
void merge(vector<int>& arr, int left, int mid, int right) {
    // We have to merge arr[left...mid] and arr[mid+1...right]
    // We will use 2-pointers technique to merge the two halves
    // Whoever has the smaller element will be added to the merged array first, and respective pointer will be incremented.
    int i = left;       // Start of left half
    int j = mid + 1;    // Start of right half
    vector<int> temp;   // Temporary array to store merged result

    while (i <= mid && j <= right) {  // While both halves have elements to compare
        // Compare elements from both halves and add the smaller one to the temp array
        // If arr[i] is smaller or equal, add it to temp and increment i, else add arr[j] and increment j
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Append remaining elements (if any)
    while (i <= mid) temp.push_back(arr[i++]);  // If left half has remaining elements, add them to temp
    while (j <= right) temp.push_back(arr[j++]);  // If right half has remaining elements, add them to temp

    // Copy merged result back to original array
    for (int k = 0; k < temp.size(); ++k) { // Copy elements from temp back to arr
        // Copying back to the original array from left index
        // left + k gives the correct index in the original array
        // This ensures that we are placing the sorted elements back in the correct positions
        arr[left + k] = temp[k];
    }
}

// Recursive merge sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;  // Base case: one or zero elements, if we have only one element or no element, then it is already sorted

    int mid = left + (right - left) / 2;  // Find mid

    // Recursively sort left and right halves
    mergeSort(arr, left, mid);  // Sort the left half
    mergeSort(arr, mid + 1, right); // Sort the right half

    // Merge the sorted halves
    merge(arr, left, mid, right); // Merge the two sorted halves
}

// Driver code
int main() {
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 6};
    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}

// Time Complexity: O(n log n) - The array is divided into halves log(n) times, and merging takes O(n) time.
// Space Complexity: O(n) - The temporary array used for merging takes O(n) space in the worst case.
