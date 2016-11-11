#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
 * Kth Permutation
 * This file contains two algorithms
 * one of which is designed to return
 * the kth permutation of a given list of
 * numbers, and the other works in reverse,
 * taking in a permutation of numbers and telling
 * you what permutation number it is.
 *
 * Complexity breakdown of both algorithms:
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 */

/**
 * Iterative function to
 * calculate the factorial
 * of some given number.
 */
int fact(int n) {
  int factN = 1;

  for (int i = 2; i <= n; ++i) {
    factN *= i;
  }

  return factN;
}

 void printVec(vector<int> v) {
   cout << "[ ";

   for (int i = 0; i < v.size(); ++i) {
     cout << v[i];
     if (i + 1 < v.size()) cout << ", ";
   }

   cout << " ]" << endl;
 }

 /**
  * This function is designed to compute the kth permutation of
  * some list of integers. The function throws a logic error if
  * the input k is <= 0 or > n!. For example given a list of 4 integers
  * we are allowed to calculate the 1st permutation, through the 24th permutation.
  *
  * Given the nature of factorial we know there will be (n-1)! permutations
  * that start with array[0], (n-1)! that start with array[1], ..., and finally
  * (n-1)! permutations that start with array[n-1]. Now imagine all permutations,
  * ordered, in one tall column. Note we'll never actually generate this list of all
  * permutations, but we can use math to figure out how to traverse this theoretical
  * list if it did exist.
  *
  * We first want to figure out the first number that the kthpermutation will start with.
  * In order to do this we need to see how far k would be down in our theoretical list of
  * permutations. More specifically we need to see which group k falls into. Does k fall
  * into the group of permutations that start with array[0], array[1], ..., or array[n].
  * Well since we know there are (n-1)! of these, we can simply divide k/(n-1)! and this
  * floor division will give us i, such that the first number of the kth permutation is
  * array[i].
  *
  * Before doing anything else we need to remove the a[i], the number that we just used from
  * our list of available numbers. We continue, however notice we've narrowed our theoretical
  * permutation list down from n! to (n-1)! possible permutations all starting with the same first
  * number. Now it is time to figure out what the second number of the kth permutation is. The same
  * pattern we saw in our previous list of n! permutations is in fact visible in our narrowed down
  * list. Sure, all of the permutations in this new list have the same first number, however note that
  * there are (n-2)! permutations in this adjusted list whose second number is array[0], (n-2)! permutations
  * whose second number is array[1] and so on. Now we need to figure out how deep k will get us in THIS list.
  * Before we do this, we need to adjust k though. Realize that the first permutation in our new list could
  * very well have been been the 1st, 7th, 13th, or 19th permutation in our theoretical list of n! permutations.
  * Since we have adjusted this permutation to be the 1st in our assumed list of (n-1)! perms, we must also adjust
  * the value of k = k%(n-1)!. Rinse and repeat my dear friends.
  *
  * Time complexity: O(n^2) because of factorial calculation every loop (and vector::erase)
  * Space complexity: O(n)
  */
vector<int> kthPermutation(vector<int> arr, int k) {
  if (k <= 0 || k > fact(arr.size())) throw logic_error(string("K cannot be greater than " + to_string(fact(arr.size()))));

  vector<int> kthPermutation;
  int indexToPush, narrowedPerm;

  while (arr.size()) {
    narrowedPerm = fact(arr.size() - 1);
    indexToPush = k / narrowedPerm;

    kthPermutation.push_back(arr[indexToPush]);
    arr.erase(arr.begin() + (indexToPush));

    k %= narrowedPerm;
  }

  return kthPermutation;
}

/**
 * This function is designed to take in some
 * permutation of numbers and return the permutation
 * of this list compared to its sorted version. It pretty
 * much works in the reverse way of the previous algorithm
 * with a couple of sneaky things...but hey, it's lit.
 *
 * Time complexity: O(n^2) because of vector erase (it is possible to optimize this out)
 * Space complexity: O(n) because we're storing the first permutation in a vector
 */
int countPermNumber(vector<int> arr) {
  vector<int> sortedArr = arr;
  sort(sortedArr.begin(), sortedArr.end());

  int kthAtLeast = 0, indexFoundInSorted, narrowedPerm;

  int i = 0;

  while (sortedArr.size()) {
    narrowedPerm = fact(sortedArr.size() - 1);
    indexFoundInSorted = distance(sortedArr.begin(), find(sortedArr.begin(), sortedArr.end(), arr[i]));

    kthAtLeast += (indexFoundInSorted)*narrowedPerm;

    sortedArr.erase(sortedArr.begin() + indexFoundInSorted);

    i++;
  }

  return kthAtLeast + 1;
}

void optionFindKthPermutation() {
  int n, k;

  cout << "Please input the number of items in your list:" << endl;
  cin >> n;

  cout << "Please type in the list of " << n << " space separated integers you would like to permute:" << endl;
  vector<int> v(n);

  for (int i = 0; i < v.size(); ++i) {
    cin >> v[i];
  }

  cout << "Please type in the permutation of this list you would lke to find" << endl;
  cin >> k;

  try {
    v = kthPermutation(v, k-1);
    cout << "The kth permutation is:" << endl;
    printVec(v);
  } catch (const std::logic_error& e) {
    cout << e.what() << endl;
  }

}

void optionCountPermutationNumber() {
  int n;

  cout << "Please input the number of items in your permutation:" << endl;
  cin >> n;

  cout << "Please type in your permutation as a list of " << n << " space separated integers:" << endl;
  vector<int> v(n);

  for (int i = 0; i < v.size(); ++i) {
    cin >> v[i];
  }

  cout << "The permutation you have entered is the " << countPermNumber(v) << " permutation" << endl;
}

int main() {

  while (1) { // until user quits

    cout << "Enter the character that corresponds to your choice:" << endl;
    cout << "    Type 'a' to find the kth permutation of a list of integers" << endl;
    cout << "    Type 'b' to find what number permutation some list of integers is" << endl;
    cout << "    Type 'q' to exit" << endl;
    char choice;
    cin >> choice;

    if (choice == 'a') {
      optionFindKthPermutation();
    } else if (choice == 'b') {
      optionCountPermutationNumber();
    } else {
      break;
    }

  }

  return 0;
}
