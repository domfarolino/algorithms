#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>

/**
 * This is a modification of the climbing stairs algorithm, designed to
 * not only return the number of unique step combinations to the top, but
 * return all actual step combinations themselves.
 */

std::vector<std::vector<int>> allPathsTopDown(int n, std::unordered_map<int, std::vector<std::vector<int>>>& uMap) {
  // Assert: uMap contains our base cases so we don't have to consider them.
  // Assert: n >= 0.
  std::vector<std::vector<int>> returnVec;
  if (uMap.find(n) != uMap.end())
    return uMap[n];


  std::vector<std::vector<int>> nMinus1 = allPathsTopDown(n - 1, uMap),
                                nMinus2 = allPathsTopDown(n - 2, uMap);

  for (int i = 0; i < nMinus1.size(); ++i)
    nMinus1[i].push_back(n);

  for (int i = 0; i < nMinus2.size(); ++i)
    nMinus2[i].push_back(n);

  returnVec.insert(returnVec.end(), nMinus1.begin(), nMinus1.end());
  returnVec.insert(returnVec.end(), nMinus2.begin(), nMinus2.end());

  uMap.insert({n, returnVec});
  return returnVec;
}

std::vector<std::vector<int>> allPathsBottomUp(int n) {
  if (n == 0)
    return {{}};

  // Assert: n > 0.
  std::vector<std::vector<int>> first = {{1}}, second = {{1, 2}, {2}}, tmp;
  int i = 2;
  while (i <= n) {
    i++;
    tmp = second;
    for (std::vector<int>& firstPath: first)
      firstPath.push_back(i);

    for (std::vector<int>& secondPath: second)
      secondPath.push_back(i);

    second.insert(second.end(), first.begin(), first.end());
    first = tmp;
  }

  return first;
}

void printPath(const std::vector<int>& path) {
  for (int num: path) {
    std::cout << num << " -> ";
  }

  std::cout << std::endl;
}

int main() {
  std::unordered_map<int, std::vector<std::vector<int>>> memo;

  // Initialize base-cases
  memo.insert({0, {{}}});
  memo.insert({1, {{1}}});
  memo.insert({2, {{1, 2}, {2}}});

  // This section below takes in a number of tests `t`, and for each test,
  // asks for an `n`, runs both algorithms, and prints their results.
  int t;
  std::cout << "How many tests do you want to run?: ";
  std::cin >> t;

  int n;
  std::vector<std::vector<int>> returnPaths1, returnPaths2;
  for (int i = 0; i < t; ++i) {
    std::cout << "Enter n: ";
    std::cin >> n;
    returnPaths1 = allPathsTopDown(n, memo);
    returnPaths2 = allPathsBottomUp(n);
    std::cout << "Paths returned from top-down solution:" << std::endl;
    for (const std::vector<int>& path: returnPaths1)
      printPath(path);

    std::cout << "Paths returned from bottom-up solution:" << std::endl;
    for (const std::vector<int>& path: returnPaths2)
      printPath(path);
  }

  // This section below generates increasing `n`s, runs both algorithms with `n`
  // and times their invocations. It outputs data suitable for plotting.
  /*
  int s = 32;
  std::cout << "Size" << '\t' << "All paths top-down (memoization)" << '\t' << "All paths bottom-up" << std::endl;
  for (int i = 2; i <= s; i++) {
    memo.insert({0, {{}}});
    memo.insert({1, {{1}}});
    memo.insert({2, {{1, 2}, {2}}});

    clock_t clock_a_start = clock();
    allPathsTopDown(i, memo);
    clock_t clock_a_stop = clock();

    clock_t clock_b_start = clock();
    allPathsBottomUp(i);
    clock_t clock_b_stop = clock();

    std::cout << i << '\t';
    std::cout << (float)(clock_a_stop - clock_a_start)/(CLOCKS_PER_SEC/1000) << '\t';
    std::cout << (float)(clock_b_stop - clock_b_start)/(CLOCKS_PER_SEC/1000) << std::endl;

    memo.clear();
  }
  */

  return 0;
}
