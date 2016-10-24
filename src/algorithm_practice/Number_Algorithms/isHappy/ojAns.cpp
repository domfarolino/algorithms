// Source: https://leetcode.com/problems/happy-number/

class Solution {
public:
    bool isHappy(int n) {
      bool set[1000] = {false};
      int tmp;

      while (n != 1) {
        tmp = 0;

        while (n) {
          tmp += (n % 10)*(n % 10);
          n /= 10;
        }

        n = tmp;

        // Can work with our set if n < 1000
        if (n < 1000) {
          if (set[n]) return false;
          else set[n] = true;
        }
      }

      return true;
    }
};
