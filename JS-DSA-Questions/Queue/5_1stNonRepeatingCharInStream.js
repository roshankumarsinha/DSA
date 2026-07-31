// Given a stream of characters, for each character read tell which character has appeared only
// once in the stream up to that point. If several, report the first to appear. If none, append '#'.

// Example:
// Input: s = "aabcdbcad" → Output: "a#bbbcdd#"

// Approach:
// 1. Use a queue to store characters that appeared exactly once (in arrival order).
// 2. Use a frequency map for character counts.
// 3. For each character: increment its count, push it to the queue, then pop from the front while
//    the front character's count > 1. The front of the queue is the first non-repeating char.
// Time Complexity: O(n). Space Complexity: O(1) (at most 26 distinct chars).

// JavaScript note: C++ used std::queue<char>. Here a plain array with push()/shift() acts as the
// queue, and a Map (or object) holds the frequencies.
function firstNonRepeatingCharacter(stream) {
  const freq = new Map();
  const q = []; // queue of characters
  let result = "";

  for (const ch of stream) {
    freq.set(ch, (freq.get(ch) || 0) + 1);
    q.push(ch);

    // Remove repeating characters from the front
    while (q.length > 0 && freq.get(q[0]) > 1) {
      q.shift();
    }

    result += q.length > 0 ? q[0] : "#";
  }
  return result;
}

const stream = "aabcdbcad";
console.log("Stream:", stream);
console.log("First non-repeating characters:", firstNonRepeatingCharacter(stream)); // a#bbbcdd#
