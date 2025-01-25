// Write a function that takes a string s. While reading characters from the stream, you have to tell which character has appeared only once in the stream upto that point. If there are many characters that have appeared only once, you have to tell which one of them was the first one to appear. If there is no such character then append '#' to the answer.

// Appraoch :-
// 1. We will use a queue to store the characters that have appeared only once in the stream.
// 2. We will use a frequency array to store the frequency of each character in the stream.(Hashmap can also be used)
// 3. We will iterate over the string and do the following:-
//    a. Increment the frequency of the current character.
//    b. If the frequency of the current character is 1, we will push it into the queue.
//    c. If the frequency of the current character is greater than 1, we will pop the front element of the queue until we get a character whose frequency is 1.
//    d. If the queue is empty, we will append '#' to the answer.
//    e. Otherwise, we will append the front element of the queue to the answer.
// 4. Return the answer.
// Time Complexity :- O(n), because we are iterating over the string only once. Outer loop will run n times and inner loop will run at max n times. Since one character can be pushed and popped at most once, the inner loop will run at max n times.
// Total time complexity = O(n) + O(n) = O(n)
// Space Complexity :- O(1), because the frequency array will have at max 26 characters.

#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

string firstNonRepeatingCharacter(string stream) {
    unordered_map<char, int> freq; // To store the frequency of characters
    queue<char> q;                // To maintain the order of characters
    string result = "";

    for (char ch : stream) {
        // Increment the frequency of the character
        freq[ch]++;

        // Add the character to the queue
        q.push(ch);

        // Remove characters from the front of the queue if they are repeating. i.e. freq > 1 or not present in the stream
        while (!q.empty() && freq[q.front()] > 1) {
            q.pop();
        }

        // Print the first non-repeating character or '#' if none exists
        if (!q.empty()) {
            result += q.front();
        } else {
            result += '#';
        }
    }
    return result;
}

int main() {
    string stream = "aabcdbcad";
    cout << "Stream: " << stream << endl;
    cout << "First non-repeating characters: " << firstNonRepeatingCharacter(stream) << endl;

    return 0;
}

