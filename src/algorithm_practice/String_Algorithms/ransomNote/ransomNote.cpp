#include <iostream>
#include <string>

// Source: https://leetcode.com/problems/ransom-note/

/**
 * Ransom Note
 * Very similar to `findTheDifference` - see this algorithm
 *
 * This is a classic algorithm to test your ability to detect whether
 * some string contains the characters, in sufficient quantity, to construct
 * some target string. It can be solved by creating a hash table storing the number
 * of times a character appears in the larger string. We then need to see if our target
 * string can be constructed from the characters in the hash table. We do this by iterating
 * through each character in the target string and checking the number of times it appeared
 * in the hash table. If the value given some character is > 0, we decrement the value in the
 * table to account for us using one of those characters. If we ever need to use a character
 * whose value in the table (number of appearances) is 0, we know it cannot be done.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity O(n) // has table
 */

bool canConstruct(const std::string& ransomNote, const std::string& magazine) {
  int hashTable[26] = {0}; // init elements => 0
  for (int i = 0; i < magazine.size(); ++i) {
    hashTable[magazine[i] - 'a']++;
  }

  for (int i = 0; i < ransomNote.size(); ++i) {
    // Must check before we decrement
    if (hashTable[ransomNote[i] - 'a'] == 0) {
      return false;
    } else {
      hashTable[ransomNote[i] - 'a']--;
    }
  }

  return true;
}

int main() {
  std::string note, bank;

  while (std::cin >> note >> bank) {
    canConstruct(note, bank) ? std::cout << "true" : std::cout << "false";
    std::cout << std::endl;
  }

  return 0;
}
