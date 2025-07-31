// Write a function to find the celebrity in a party of n people.

// You are given a n x n matrix M, where:
//  M[i][j] == 1 means person i knows person j
//  M[i][j] == 0 means person i does not know person j

// A celebrity is someone who:
//  Is known by everyone else (M[x][i] == 1 for all i ≠ x)
//  Knows no one (M[i][x] == 0 for all i ≠ x)

// Example: 
// M = [
//   [0, 1, 0],
//   [0, 0, 0],
//   [0, 1, 0]
// ]
// Person 1 is a celebrity:
// Everyone knows person 1.
// Person 1 knows no one.


// Intuition:
// 1. A celebrity is a person who is known by everyone else but knows no one. That means we can have either 0 celebrity or max 1 celebrity in a party.
//    We will use this knowledge only to find the celebrity.
// 2. We will find the potential celebrity, by eliminating all people and keeping just one potential celebrity.
// 3. At last we will verify whether the potential celebrity is actually a celebrity or not.

// Approach 1: (Using Stack)
// 1. Push all people into a stack.
// 2. Pop two people at a time and check if one knows the other.
//    - If person A knows person B, then A cannot be a celebrity, so we pop A and push B back onto the stack.
//    - If person A does not know person B, then B cannot be a celebrity, so we pop B and push A back onto the stack.
// 3. After processing all pairs, only one person will remain in the stack, which is the potential celebrity.
// 4. Verify if this person is a celebrity by checking if they are known by everyone and know no one.
// 5. If they meet the criteria, return their index; otherwise, return -1.
// Time Complexity: O(n) for finding the potential celebrity and O(n) for verification, resulting in O(n) overall.
// Space Complexity: O(n) for the stack.

// Approach 2: (Using Two Pointers)
// 1. Initialize two pointers, left and right, at the start and end of the array.
// 2. Compare the people at these pointers:
//    - If left knows right, then left cannot be a celebrity, so move the left pointer to the right.
//    - If left does not know right, then right cannot be a celebrity, so move the right pointer to the left.
// 3. After processing, only one person will remain, which is the potential celebrity.
// 4. Verify if this person is a celebrity by checking if they are known by everyone and know no one.
// 5. If they meet the criteria, return their index; otherwise, return -1.
// Time Complexity: O(n) for finding the potential celebrity and O(n) for verification, resulting in O(n) overall.
// Space Complexity: O(1) for using only a few variables.



// Approach 1: (Using Stack)
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Function to check if person a knows person b
bool knows(const vector<vector<int>>& M, int a, int b) {
    return M[a][b] == 1;
}

// Main function to find the celebrity
int findCelebrity(vector<vector<int>>& M, int n) {
    stack<int> st;

    // Step 1: Push everyone onto the stack
    for (int i = 0; i < n; ++i) {
        st.push(i);
    }

    // Step 2: Eliminate non-celebrities
    while (st.size() > 1) { // While we left with only one person
        int a = st.top(); st.pop();
        int b = st.top(); st.pop();

        if (knows(M, a, b)) {
            // a cannot be celebrity
            st.push(b);
        } else {
            // b cannot be celebrity
            st.push(a);
        }
    }

    // Step 3: Verify the candidate
    // So for this index we will check if it is a celebrity or not
    // So, for celebrity all the columns for that index should be 0 and all the rows for that index should be 1
    int candidate = st.top();
    st.pop();

    for (int i = 0; i < n; ++i) {
        if (i != candidate) {
            // Check if candidate knows someone
            if (knows(M, candidate, i)) {
                return -1; // Candidate knows someone, so not a celebrity
            }
            // Check if someone knows the candidate
            if (!knows(M, i, candidate)) {
                return -1; // Someone does not know the candidate, so not a celebrity
            }
        }
    }

    return candidate;
}

int main() {
    vector<vector<int>> M = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };

    int n = M.size();
    int result = findCelebrity(M, n);
    if (result == -1) {
        cout << "No celebrity found.\n";
    } else {
        cout << "Celebrity is person " << result << ".\n";
    }

    return 0;
}



// Approach 2: (Using Two Pointers)
#include <iostream>
#include <vector>
using namespace std;

// Simulate "knows" function
bool knows(const vector<vector<int>>& M, int a, int b) {
    return M[a][b] == 1;
}

int findCelebrity(vector<vector<int>>& M, int n) {
  int i = 0;
  int j = n - 1;

  // Step 1: Eliminate non-celebrities
  while (i < j) {
      if (knows(M, i, j)) {
          // i knows j => i can't be celeb
          i++;
      } else {
          // i doesn't know j => j can't be celeb
          j--;
      }
  }

  int candidate = i;

  // Step 2: Verify candidate
  for (int k = 0; k < n; ++k) {
      if (k != candidate) {
          if (M[candidate][k] == 1 || M[k][candidate] == 0) {
              return -1; // Not a celebrity
          }
      }
  }

  return candidate;
}


int main() {
    vector<vector<int>> M = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };

    int n = M.size();
    int result = findCelebrity(M, n);

    if (result == -1)
        cout << "No celebrity found.\n";
    else
        cout << "Celebrity is person " << result << ".\n";

    return 0;
}

