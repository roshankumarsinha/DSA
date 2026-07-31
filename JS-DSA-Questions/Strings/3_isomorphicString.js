/*
    =====================================================
    ISOMORPHIC STRINGS
    =====================================================

    Problem: Given two strings s and t, determine if they are isomorphic.
    Two strings are isomorphic if the characters in s can be replaced to
    get t, with the following rules:
    1. Each character in s maps to EXACTLY one character in t.
    2. No two characters in s map to the SAME character in t (one-to-one).
    3. The mapping must preserve the order of characters.

    Example:
    Input: s = "egg", t = "add"     → true  (e → a, g → d)
    Input: s = "foo", t = "bar"     → false (o maps to both 'a' and 'r')
    Input: s = "paper", t = "title" → true  (p → t, a → i, e → l, r → e)
    Input: s = "badc", t = "baba"   → false (d → b and a → b collide)

    =====================================================
    INTUITION:
    =====================================================

    We need a BIDIRECTIONAL one-to-one mapping between characters.

    Why bidirectional?
    - s → t mapping alone is NOT enough
    - Example: s = "badc", t = "baba" — d→b fails because b is already
      mapped FROM b
    - We need to ensure no two chars in s map to the SAME char in t

    Solution: Use TWO MAPS
    - mapST: s[i] → t[i] (what does each char in s map to in t?)
    - mapTS: t[i] → s[i] (what does each char in t map to in s?)

    For each position i, check:
    1. If s[i] already has a mapping, it must map to t[i]
    2. If t[i] already has a mapping, it must map to s[i]
    3. If neither has a mapping, create both mappings

    =====================================================
    APPROACH:
    =====================================================
    1. If lengths differ, return false
    2. Create two maps: mapST and mapTS
    3. For each index i:
       a. If s[i] is in mapST and mapST[s[i]] != t[i] → return false
       b. If t[i] is in mapTS and mapTS[t[i]] != s[i] → return false
       c. Otherwise, set mapST[s[i]] = t[i] and mapTS[t[i]] = s[i]
    4. Return true

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through both strings
    SPACE COMPLEXITY: O(1) - At most a constant number of character mappings
    =====================================================
*/

// In C++ we used unordered_map<char, char>. In JavaScript, the idiomatic choice is a Map
// (or a plain object). Using a Map with `.has()` / `.get()` is safe and avoids the C++ bug
// where a default-constructed '\0' value could be treated as "no mapping".
function isIsomorphic(s, t) {
  // Step 1: If lengths differ, they cannot be isomorphic
  if (s.length !== t.length) return false;

  // Step 2: Create two maps for bidirectional mapping
  const mapST = new Map(); // s[i] → t[i]
  const mapTS = new Map(); // t[i] → s[i]

  for (let i = 0; i < s.length; i++) {
    // Check s → t mapping
    if (mapST.has(s[i]) && mapST.get(s[i]) !== t[i]) {
      return false;
    }

    // Check t → s mapping (prevents two chars mapping to same target)
    if (mapTS.has(t[i]) && mapTS.get(t[i]) !== s[i]) {
      return false;
    }

    mapST.set(s[i], t[i]);
    mapTS.set(t[i], s[i]);
  }

  // All checks passed, they are isomorphic
  return true;
}

console.log(isIsomorphic("egg", "add")); // true
console.log(isIsomorphic("foo", "bar")); // false
console.log(isIsomorphic("paper", "title")); // true
console.log(isIsomorphic("badc", "baba")); // false
