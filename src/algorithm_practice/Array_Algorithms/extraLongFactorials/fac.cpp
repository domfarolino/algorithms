#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Source: https://www.hackerrank.com/challenges/extra-long-factorials
// Stackoverflow post: http://stackoverflow.com/questions/39092964/calculating-large-factorial-time-complexity

/**
 * Extra Long Factorials
 *
 * One good way to store massive numbers (especially numbers that cannot
 * fit inside a 64 bit integer) is to use arrays/vectors to represent the number.
 * After realizing that storage of obscenely large numbers isn't an issue at at all
 * we just need to look the mechanics of multiplying a number represented by a vector,
 * by an actual scalar. The naive way of course is to take advantage of our ability to
 * easily add two vectors together. If we need to multiply a vector representation by say
 * 5, we just add it to itself 5 times. The addVectors function has a runtime proportional
 * to the length of the number represented by a vector, or namely log10(k) where k is said
 * number. The function to multiply a vector by some scalar n will just call the addVector
 * function n times with slightly larger vector representations. The process will look something
 * like this: when given an integer j and a vector representation of k, we see the following accumulated
 * addVector steps: O(2log(k)) + O(3log(k)) + ... + O(jlog(k)). In our case, we know j will always be the
 * integer value of the factorial we are trying to compute, and k will always be a vector representation of
 * (j-1)!. Of course j*(j-1)! = j! which is what we're trying to get a vector representation for thus we need
 * j additions of k, or j-1 calls to the addVector() function. With this knowledge, the accumulated steps will
 * look like this: O(log(2(j-1!))) + O(log(3(j-1!))) + ... + O(log(j(j-1!))). The last term can be expressed as
 * O(log(j!)). Since we have O(j) of the above terms the complexity for the function can be roughly written as O(jlog(j!))
 * or O(j^2log(j)) (remember that Theta(log(n!)) = Theta(nlog(n))). Since in order to find the factorial of a number
 * we must call the multiplyVectorByIntegerNaive() function n times with values from 1..n, the total complexity for this
 * method can be written as O(n^3og(n)) or O(n^2log(n!)). While this complexity is asymptotically atrocious remember n
 * in practice will probably never be larger than a few hundred.
 *
 * Note in the above method the vector representation of an integer can be stored with its least significant digit either
 * at the beginning or the end.
 *
 * Time complexity: O(n^2log(n!)) = O(n^3log(n))
 * Space complexity: O(log(n!)) - because we need a vector large enough to hold at most n!
 *
 * The simpler and more efficient way is to multiply a vector representation of a number by some number k in
 * a way that such that the multiply function has a running time proportional to the length of the resulting vector.
 * Let's analyze how we would multiply a number by some number k. Assume we have the number 25683 that we want to multiply by k = 34.
 * Let's realize that that answer can be broken down as follows:
 *           3*34
 *     +    80*34
 *     +   600*34
 *     +  5000*34
 *     + 20000*34
 *
 * Let's look at the mechanics of how our multiply function might work. We could just calculate each place in our resulting vector
 * one at a time, which would mean we want to start at the least significant digit (3) and do a multiplication. 3*34 = 102, it is clear
 * that the last number of our resulting vector will be 102%10 = 2. Since 102 is too significant for the 1s place, we must properly truncate
 * it and carry some of it over to the next most significant place so it can be evaluated with our next multiplication. We've already used the
 * 2 from 102, and only the 10 from our 102 is significant to the next place value so we need to take 102 and divide it by 10. Since we're now
 * about to set the next most significant digit in our resulting vector, we don't need to multiply 80*34, but instead only need to worry about 8*34.
 * The trailing 0s are used to indicate its significance however we're already accounting for that by moving over one place value in our resulting answer
 * vector. Of course we also need to look at what was carried over from our previous multiplication before finishing. We can calculate the value in this place
 * as (carry + 8*34)%10 = (10 + 8*34)%10 which is similar to our previous calculation. The next carry value will need to be the result divided by 10 = (10 + 8*34)/10
 * which consists of all integers too significant for the current (10s) place. If we keep going, we can notice that our carry value alone can get rather large. All of
 * the digits in the carry value are too significant for the current place, so when we finish multiplying through our input vector, if we still have values in our carry
 * integer we need to add them digit by digit to our resulting vector. For this, see the while loop in the multiplyVectorByInteger() function.
 *
 * With this optimization, the multiplyVectorByInteger() function becomes O(log(n*k)) where n is integer we are given and k is the number represented by the vector.
 * Given the way we'll use it, we can formulate the following complexity:
 * Time complexity: O(log(n!))
 * Space complexity: O(log(n!))
 *
 * Note in this more optimized multiplyVectorByInteger() function it would be best to accept vector representations of integers where the most significant digit
 * is at the end so when we append values from our carry integer we do not have to perform entire array shifts.
 */

/**
 * Utiility function for adding two vector representations of integers
 * Time complexity: O(log(a+b))
 * Space complexity: O(log(a+b))
 */
vector<int> addVectors(const vector<int>& a, const vector<int>& b) {
  int maxSize = max(a.size(), b.size());
  vector<int> outputVec(maxSize);

  int aIndex = a.size()-1, bIndex = b.size()-1, carry = 0;
  int aVal, bVal;

  for (int i = maxSize-1; i >= 0; --i) {
    if (aIndex < 0) aVal = 0;
    else aVal = a[aIndex];

    if (bIndex < 0) bVal = 0;
    else bVal = b[bIndex];

    outputVec[i] = (aVal + bVal + carry)%10;

    if (aVal + bVal + carry > 9) carry = 1;
    else carry = 0;

    aIndex--;
    bIndex--;
  }

  if (carry) outputVec.insert(outputVec.begin(), 1);

  return outputVec;
}

/**
 * Naive way to multiply a vector representation
 * of an integer by some scalar integer.
 * Time complexity: O(nlog(n*k)) - in our case: O(nlog(n!)) = O(n^2log(n))
 * Space complexity: O(log(n*k)) - in our case O(log(n!))
 */
vector<int> multiplyVectorByIntegerNaive(const vector<int>& numVector, int n) {
  vector<int> returnVec = numVector;

  while (n != 1) {
    returnVec = addVectors(returnVec, numVector);
    n--;
  }

  return returnVec;
}

/**
 * Optimized way to multiply a vector representation
 * of an integer by some scalar integer.
 * Time complexity: O(log(n*k)) - in our case O(log(n!))
 * Space complexity: O(log(n*k)) - in our case O(log(n!))
 */
vector<int> multiplyVectorByInteger(const vector<int>& numVector, int n) {
  vector<int> returnVec(numVector.size());

  int carry = 0;

  for (int i = 0; i < numVector.size(); ++i) {
    returnVec[i] = (numVector[i]*n + carry) % 10;
    carry = (numVector[i]*n + carry) / 10;
  }

  while (carry) {
    returnVec.push_back(carry%10);
    carry /= 10;
  }

  return returnVec;
}

/**
 * Time complexity: O(nlog(n!)) = O(n^2log(n))
 * Space complexity: O(log(n!))
 */
int main() {
  vector<int> output = {1};
  int n;

  while (cin >> n) {

    while (n) {
      output = multiplyVectorByInteger(output, n);
      n--;
    }

    for (vector<int>::const_reverse_iterator i = output.rbegin(); i != output.rend(); ++i) {
      cout << *i;
    }

    cout << endl;
    output = {1};
  }

  return 0;
}
