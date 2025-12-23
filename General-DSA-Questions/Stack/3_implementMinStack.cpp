// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

// Notes : https://takeuforward.org/data-structure/implement-min-stack-o2n-and-on-space-complexity/

// Approach 1 : (using pairs to store value and min)
// 1. Use a stack to store pairs of integers, where each pair contains the value and the minimum value at that point.
// 2. When pushing a new value, compare it with the current minimum (top of the stack) and push a new pair containing the value and the minimum
// 3. When popping, simply pop the top pair from the stack.

// class MinStack {
//   stack <pair <int, int>> st;

//   public:
//     void push(int x) {
//       int min;
//       if (st.empty()) {
//         min = x;
//       } else {
//         min = min(st.top().second, x);
//       }
//       st.push({x,min});
//     }

//   void pop() {
//     st.pop();
//   }

//   int top() {
//     return st.top().first;
//   }

//   int getMin() {
//     return st.top().second;
//   }
// };

// Approach 2 : (Using just single stack)
// 1. Push : Now if there is a push operation just check whether that number is less than the min number.
//    If it is smaller than min we will push a modified value which is a push(2 * CurrentValue - PreviousMin) into the stack and will update min to the value of the current number.
//    If it’s not then we will just push it as it is.
// 2. getMin : We will just return the value of min.
// 3. Top value : If the value is less than min then it says we have stored the modified value and we will return the value of min, otherwise we will return the top value of the stack.
// 4. Pop : While making pop we will check if the top value is lesser than min, If it is then we must update our min to its previous value. In order to do that min = (2 * min) - (modified value) and we will pop the element.

// How we derive this formula?
// 1. Wehen we are pushing a modified value, we are essentially storing the difference between the current value and the previous minimum.
//    Modified value = 2 * CurrentValue - PreviousMin.
// 2. When we pop, if the popped value is modified, we can retrieve the previous minimum using the formula: PreviousMin = 2 * CurrentMin - PoppedValue. But PoppedValue is the modified value.
//    so, PreviousMin = 2 * CurrentMin - (2 * CurrentValue - PreviousMin) = PreviousMin.


// Note: It's not necessary to use M.V = 2 * C.V - P.M formula, any formula that maintains the relationship and allows retrieval of previous minimum can be used.
// like we can use M.V = C.V - P.M instead and update the previous min accordingly during pop operation. We just need to keep in mind
// that we don't want to lose the information of previous minimum while pushing new minimum values.

#include <iostream>
#include<stack>
#include<limits.h>
using namespace std;

class SpecialStack {
    // Define the data members.
	  stack<int> s;
    int mini = INT_MAX; // Initialize mini to the maximum possible integer value
    /*----------------- Public Functions of SpecialStack -----------------*/
    public:
        
    void push(int data) {
        //for first element
        if (s.empty()) {
          s.push(data);
          mini = data;
        }
        else {
         	if (data < mini) {
              s.push(2*data - mini);  // Add modified value
              mini = data;
          } else {
              s.push(data); // Add normal value
          }
        }
    }

    int pop() {
        if (s.empty()) {
            return -1;
        }
        
        int curr = s.top();
        s.pop();
        if(curr > mini) { // If the popped value is not modified, Simply return the popped value
            return curr;
        }
        else  // If the popped value is modified, we need to update mini and return the previous minimum
        {
            int prevMin = mini;
            int val = 2*mini - curr;
            mini = val;
            return prevMin;
        }
    }

    int top() {
        if(s.empty())
            return -1;
        
        int curr = s.top();
        if(curr < mini) { // If the top value is modified, return the current minimum
            return mini;
        }
        else  // If the top value is not modified, return the top value
        {
            return curr;
        }
    }

    bool isEmpty() {
        return s.empty();
    }

    int getMin() {
        if(s.empty())
            return -1;
        
        return mini;
    }  
};