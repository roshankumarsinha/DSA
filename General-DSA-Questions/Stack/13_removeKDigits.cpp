// Given a string nums representing a non-negative integer, and an integer k,
// find the smallest possible integer after removing k digits from num.

// Example:
// Input: nums = "541892", k = 2
// Output: "1892" 
// Explanation: Remove the digits '5' and '4' to form the new number "1892", which is the smallest possible.

// Input: nums = "1002991", k = 3
// Output: "21"
// Explanation: Remove the digits '1', '9' and '9' to form the new number "0021", which is "21" after removing leading zeros.


// Intuition:
// 1. We can use a stack to build the smallest number by iterating through each digit in the string.
// 2. For each digit, we compare it with the top of the stack.
// 3. If the current digit is smaller than the top of the stack and we still have digits left to remove (k > 0), we pop the top of the stack.
// 4. We are doing step 3 to ensure that we can pop all larger digits before the current smaller digit to form a smaller number, if k allows.
// 5. We continue this process until we have processed all digits in the string.
// 6. If there are still digits left to remove after processing all digits, we remove them from the end of the stack.
// 7. Finally, we construct the result from the stack and remove any leading zeros.

// Explanation of approach with example "541892", k = 2:
// - Start with an empty stack.
// - Read '5': Stack = [5]
// - Read '4': '4' < '5' and k > 0, pop '5', Stack = [4], k = 1
// - Read '1': '1' < '4' and k > 0, pop '4', Stack = [1], k = 0
// - Read '8': Stack = [1, 8], since k = 0, we just push
// - Read '9': Stack = [1, 8, 9], since k = 0, we just push
// - Read '2': Stack = [1, 8, 9, 2], since k = 0, we just push
// - k is now 0, so we stop popping.
// - The final stack is [1, 8, 9, 2] which gives us "1892".

// Second example "1002991", k = 3:
// - Start with an empty stack.
// - Read '1': Stack = [1]
// - Read '0': '0' < '1' and k > 0, pop '1', Stack = [0], k = 2
// - Read '0': Stack = [0, 0], since k > 0 but '0' is not less than '0', we just push
// - Read '2': Stack = [0, 0, 2], since k > 0 but '2' is not less than '0', we just push
// - Read '9': Stack = [0, 0, 2, 9], since k > 0 but '9' is not less than '2', we just push
// - Read '9': Stack = [0, 0, 2, 9, 9], since k > 0 but '9' is not less than '9', we just push
// - Read '1': '1' < '9' and k > 0, pop '9', Stack = [0, 0, 2, 9], k = 1
// - '1' < '9' and k > 0, pop '9', Stack = [0, 0, 2], k = 0
// - Push '1': Stack = [0, 0, 2, 1]
// - k is now 0, so we stop popping.
// - The final stack is [0, 0, 2, 1] which gives us "0021". After removing leading zeros, we get "21".


#include <iostream>
#include <stack>
#include <string>
using namespace std;

string removeKDigits(string num, int k) {
    stack<char> st;

    for (char digit : num) {
        // While we can remove more digits and the current digit is smaller than the top of the stack
        while (!st.empty() && k > 0 && st.top() > digit) {
            st.pop(); // Remove the larger digit
            k--;      // Decrease the count of digits to remove
        }
        st.push(digit); // Push the current digit onto the stack
    }

    // If there are still digits to remove, remove them from the end
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }

    // Construct the result from the stack
    string result;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    // Remove leading zeros
    while (result.length() > 0 && result.back() == '0') {
        result.pop_back();
    }

    // Edge case: if the result is empty, return "0"
    if (result.empty()) {
        return "0";
    }

    // Reverse to get the correct order
    reverse(result.begin(), result.end());

    return result;
}

int main() {
    string num1 = "541892";
    int k1 = 2;
    cout << "Result after removing " << k1 << " digits from " << num1 << ": " << removeKDigits(num1, k1) << endl;

    string num2 = "1002991";
    int k2 = 3;
    cout << "Result after removing " << k2 << " digits from " << num2 << ": " << removeKDigits(num2, k2) << endl;

    return 0;
}

// Time Complexity: O(n), where n is the length of the input string num. Each digit is pushed and popped from the stack at most once.
// Space Complexity: O(n) in the worst case, where all digits are kept in the stack.