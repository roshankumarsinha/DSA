// Given an array of asteroids, where each asteroid is represented by an integer, determine the state of the asteroids after all collisions.
// The absolute value of the integer represents the size of the asteroid, and the sign represents its direction (positive for right, negative for left).
// When two asteroids collide, the smaller one explodes. If both are the same size, both explode. Asteroids moving in the same direction do not collide.
// All asteroids move at the same speed. We need to find the final state of the asteroids after all collisions.

// Example:
// Input: asteroids = [5, 10, -5]
// Output: [5, 10]
// Explanation: The asteroid 10 and -5 collide resulting in 10. The asteroid -5 explodes.

// Example 2:
// Input: asteroids = [8, -8]
// Output: []
// Explanation: The asteroids 8 and -8 collide resulting in both asteroids exploding.

// Example 3:
// Input: asteroids = [4, 7, 1, 1, 2, -3, -7, 17, 15, -16]
// Output: [4, 17]
// Explanation: The asteroids 7 and -7 collide resulting in both asteroids exploding. The asteroids 1 and -3 collide resulting in -3. The asteroids 2 and -3 collide resulting in -3. The asteroids 15 and -16 collide resulting in -16. The final state of the asteroids is [4, 17].


// // Intuition:
// 1. Use a stack to keep track of the asteroids that are still moving. Why a stack?
//    Because we need to compare the current asteroid with the last one that was added to the stack (the one that is closest to it).
// 2. Iterate through each asteroid in the input list.
// 3. For each asteroid, check if it is moving left (negative) and the top of the stack is moving right (positive).
//    This is the only scenario where a collision can occur.
// 4. If a collision occurs, compare the sizes of the two asteroids:
//    - If the current asteroid is larger, pop the top of the stack (the right-moving asteroid explodes) and continue checking for further collisions.
//    - If they are the same size, pop the top of the stack and do not add the current asteroid (both explode).
//    - If the current asteroid is smaller, do not add it to the stack (it explodes).
// 5. If no collision occurs, simply push the current asteroid onto the stack.
// 6. After processing all asteroids, the stack will contain the final state of the asteroids.
// 7. There is a case when stack becomes empty during collision checks, in that case we can directly push the current asteroid onto the stack as there is nothing to collide with irrespective of its direction.
// 8. Finally, reverse the stack to get the correct order of asteroids and return it.


#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;

    for (int asteroid : asteroids) {
        // Push the ateroid onto the stack if it's moving right (positive)
        if (asteroid > 0) {
            st.push(asteroid);
        } else {
            // Current asteroid is moving left (negative), and top of stack is moving right (positive) then collision occurs
            // If top of stack asteroid is smaller than the current asteroid, it will explode
            while (!st.empty() && st.top() > 0 && st.top() < abs(asteroid)) {
                // The right-moving asteroid is smaller, it explodes
                st.pop();
            }
            // After popping smaller right-moving asteroids, check the conditions for the current left-moving asteroid if both are same size then both explode
            if (!st.empty() && st.top() == abs(asteroid)) {
                // Both asteroids are the same size, both explode
                st.pop();
            } else if (st.empty() || st.top() < 0) {    // If stack is empty or top of stack asteroid is also moving left then no collision occurs, push the current asteroid onto the stack
                // No collision, push the left-moving asteroid onto the stack
                st.push(asteroid);
            }
        }
    }

    vector<int> result; // To store the final state of asteroids, we need to reverse the stack to get the correct order
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    reverse(result.begin(), result.end());

    return result;
}

int main() {
    vector<int> asteroids = {4, 7, 1, 1, 2, -3, -7, 17, 15, -16};
    vector<int> result = asteroidCollision(asteroids);

    cout << "Final state of asteroids after collisions: ";
    for (int asteroid : result) {
        cout << asteroid << " ";
    }
    cout << endl;

    return 0;
}

// Time Complexity: O(n), where n is the number of asteroids. Each asteroid is pushed and popped from the stack at most once.
// Space Complexity: O(n) in the worst case, where all asteroids are moving in the same direction and none collide.