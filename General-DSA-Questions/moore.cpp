// Write a function for Moore's algorithm that finds the majority element in an array of integers.
// A majority element is an element that appears more than n/2 times where n is the size of the array.

#include <iostream>
#include <vector>

using namespace std;

int moore(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    for (int value: nums) {
        if (count == 0) {
            candidate = value;
        }
        // You can also write this as count += (value == candidate) ? 1 : -1;
        if (value == candidate) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}