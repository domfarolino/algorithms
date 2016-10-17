class Solution {
public:
  int maxRotateFunction(const vector<int>& A) {
    int currFValue = 0, sum = 0, maxFValue;

    // Set F(0) and sum
    for (int i = 0; i < A.size(); ++i) {
      currFValue += i*A[i];
      sum += A[i];
    }

    maxFValue = currFValue;

    for (int i = 0; i < A.size(); ++i) {
      currFValue -= sum;
      currFValue += A.size()*A[i];
      maxFValue = max(currFValue, maxFValue);
    }

    return maxFValue;
  }
};
