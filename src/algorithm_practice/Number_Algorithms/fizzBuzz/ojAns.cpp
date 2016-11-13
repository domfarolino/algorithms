class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> returnVec(n, "");

        for (int i = 1; i <= n; ++i) {
            if (i % 3 && i % 5) returnVec[i-1] = to_string(i);
            else if (i % 3 || i % 5) {
                (i % 3) ? returnVec[i-1] = "Buzz" : returnVec[i-1] = "Fizz";
            } else if (i % 3 == 0 && i % 5 == 0) returnVec[i-1] = "FizzBuzz";
        }

        return returnVec;
    }
};
