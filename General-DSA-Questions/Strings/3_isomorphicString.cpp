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
    Input: s = "egg", t = "add"
    Output: true
    Explanation: e → a, g → d

    Input: s = "foo", t = "bar"
    Output: false
    Explanation: o maps to both 'a' and 'r' — NOT possible

    Input: s = "paper", t = "title"
    Output: true
    Explanation: p → t, a → i, e → l, r → e

    Input: s = "badc", t = "baba"
    Output: false
    Explanation: d → b and a → b — two characters map to same target

    =====================================================
    INTUITION:
    =====================================================
    
    We need a BIDIRECTIONAL one-to-one mapping between characters.

    Why bidirectional?
    - s → t mapping alone is NOT enough
    - Example: s = "badc", t = "baba"
      Forward: b→b, a→a, d→b, c→a — d→b fails because d maps to b 
      but b is already mapped FROM b
    - We need to ensure no two chars in s map to the SAME char in t

    Solution: Use TWO HASHMAPS
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
    2. Create two hashmaps: mapST and mapTS
    3. For each index i:
       a. If s[i] is in mapST and mapST[s[i]] != t[i] → return false
       b. If t[i] is in mapTS and mapTS[t[i]] != s[i] → return false
       c. Otherwise, set mapST[s[i]] = t[i] and mapTS[t[i]] = s[i]
    4. Return true

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: s = "paper", t = "title"
    mapST = {}, mapTS = {}

    i=0: s='p', t='t'
        'p' not in mapST, 't' not in mapTS
        mapST = {p:t}, mapTS = {t:p}

    i=1: s='a', t='i'
        'a' not in mapST, 'i' not in mapTS
        mapST = {p:t, a:i}, mapTS = {t:p, i:a}

    i=2: s='p', t='t'
        'p' in mapST → mapST['p'] = 't' == 't' ✓
        't' in mapTS → mapTS['t'] = 'p' == 'p' ✓

    i=3: s='e', t='l'
        'e' not in mapST, 'l' not in mapTS
        mapST = {p:t, a:i, e:l}, mapTS = {t:p, i:a, l:e}

    i=4: s='r', t='e'
        'r' not in mapST, 'e' not in mapTS
        mapST = {p:t, a:i, e:l, r:e}, mapTS = {t:p, i:a, l:e, e:r}

    All positions matched → return true ✓

    =====================================================
    EXAMPLE DRY RUN 2 (false case):
    =====================================================
    Input: s = "foo", t = "bar"
    mapST = {}, mapTS = {}

    i=0: s='f', t='b'
        mapST = {f:b}, mapTS = {b:f}

    i=1: s='o', t='a'
        mapST = {f:b, o:a}, mapTS = {b:f, a:o}

    i=2: s='o', t='r'
        'o' in mapST → mapST['o'] = 'a' != 'r' ✗
        return false ✓

    =====================================================
    EXAMPLE DRY RUN 3 (why we need BOTH maps):
    =====================================================
    Input: s = "badc", t = "baba"
    mapST = {}, mapTS = {}

    i=0: s='b', t='b'
        mapST = {b:b}, mapTS = {b:b}

    i=1: s='a', t='a'
        mapST = {b:b, a:a}, mapTS = {b:b, a:a}

    i=2: s='d', t='b'
        'd' not in mapST ✓
        't' in mapTS → mapTS['b'] = 'b' != 'd' ✗
        return false ✓
        (Without mapTS, we'd wrongly allow d→b since mapST doesn't have 'd')

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through both strings
    SPACE COMPLEXITY: O(1) - At most 256 ASCII character mappings
    =====================================================
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

bool isIsomorphic(string s, string t) {
    // Step 1: If lengths differ, they cannot be isomorphic
    if (s.length() != t.length()) return false;
    
    // Step 2: Create two hashmaps for bidirectional mapping
    unordered_map<char, char> mapST;  // s[i] → t[i]
    unordered_map<char, char> mapTS;  // t[i] → s[i]
    
    for (int i = 0; i < s.length(); i++) {
        // Check s → t mapping
        if (mapST[s[i]] && mapST[s[i]] != t[i]) {
            return false;
        }
        
        // Check t → s mapping (prevents two chars mapping to same target)
        if (mapTS[t[i]] && mapTS[t[i]] != s[i]) {
            return false;
        }
        
        mapST[s[i]] = t[i];
        mapTS[t[i]] = s[i];
    }
    
    // All checks passed, they are isomorphic
    return true;
}
