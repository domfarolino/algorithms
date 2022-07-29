//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility> // for std::pair
#include <unordered_map>

using namespace std;

#include "lena_sort.h"

struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

using MemoMap = std::unordered_map<std::pair<int, int>, std::vector<int>, pairhash>;

vector<string> split_string(string);

std::unordered_map<long long, long long> comparison_memo;

long long min_comparisons(long long l) {
  if (l <= 1)
    return 0;
  if (comparison_memo.find(l) != comparison_memo.end())
    return comparison_memo[l];

  long long minus = l - 1;
  long long result = minus + min_comparisons(double(minus) / 2.0 + .5) + min_comparisons(minus / 2);
  comparison_memo[l] = result;
  return result;
}

long long max_comparisons(long long l) {
  return (l * (l - 1)) / 2;
}

bool can_make_array(long long l, long long c) {
  return (c >= min_comparisons(l) &&
          c <= max_comparisons(l));
}

std::vector<int> gen_array(long long l, long long c, MemoMap& memo, std::string prefix = "") {
  if (l == 1 && c == 0) return {1};
  if (memo.find({l, c}) != memo.end())
    return memo[{l, c}];

  // Create and fill initial array.
  std::vector<int> return_array(l);
  for (int i = 0; i < return_array.size(); ++i)
    return_array[i] = i + 1;

  long long half = int(double(l) / 2.0 + .5) - 1;
  long long left_size, right_size;
  long long remaining_comps = c - (l - 1);
  bool break_flag = false;
  for (int i = 0; i <= half; ++i) {
    // Candidate pivot = return_array[i];
    //std::cout << prefix << "Considering pivot element: " << return_array[i] << std::endl;
    left_size = i;
    right_size = return_array.size() - left_size - 1;

    for (long long left_comps = 0; left_comps <= remaining_comps; ++left_comps) {

      if (can_make_array(left_size, left_comps) &&
          can_make_array(right_size, remaining_comps - left_comps)) {
        //std::cout << prefix << "Left (l, c): " << left_size << ", " << left_comps << ", Right (l, c): " << right_size << ", " << remaining_comps - left_comps << std::endl;

        std::vector<int> lhs = gen_array(left_size, left_comps, memo, prefix + " - (l) "),
          rhs = gen_array(right_size, remaining_comps - left_comps, memo, prefix + " - (r) ");
        return_array[0] = return_array[i];

        for (int j = 0; j < lhs.size(); ++j)
          return_array[j + 1] = lhs[j];
        for (int j = 0; j < rhs.size(); ++j)
          return_array[j + 1 + lhs.size()] = rhs[j] + return_array[0];

        break_flag = true;
        break;
      } else {
        //std::cout << prefix << "Failed: left (" << left_size << ", " << left_comps << ") right (" << right_size << ", " << remaining_comps - left_comps << ")" << std::endl;
      }

    }

    if (break_flag) break;
  }

  memo[{l, c}] = return_array;
  return return_array;
}

void gen_array2(std::vector<int>& arr, long long left, long long right, long long c, MemoMap& memo, std::string prefix = "") {
  if (right - left <= 0) return;

  long long l = right - left + 1;
  long long half = int(double(l) / 2.0 + .5) - 1 + left;
  half = l / 2;
  long long left_size, right_size;
  long long remaining_comps = c - (l - 1);
  bool break_flag = false;
  for (int i = left; i <= left + half; ++i) {
    // Candidate pivot = return_array[i];
    //std::cout << prefix << "Considering pivot element: " << arr[i] << std::endl;
    left_size = i - left;
    right_size = l - left_size - 1;

    for (long long left_comps = 0; left_comps <= remaining_comps; ++left_comps) {

      if (can_make_array(left_size, left_comps) &&
          can_make_array(right_size, remaining_comps - left_comps)) {
        //std::cout << prefix << "Left (l, c): " << left_size << ", " << left_comps << ", Right (l, c): " << right_size << ", " << remaining_comps - left_comps << std::endl;

        //std::swap(arr[left], arr[i]);
        int j = i;
        while (j > left) {
          std::swap(arr[j], arr[j - 1]);
          j--;
        }
        gen_array2(arr, left + 1, left + left_size, left_comps, memo, prefix + " - (l) ");
        gen_array2(arr, left + 1 + left_size, left + left_size + right_size, remaining_comps - left_comps, memo, prefix + " - (r) ");

        break_flag = true;
        break;
      } else {
        //std::cout << prefix << "Failed: left (" << left_size << ", " << left_comps << ") right (" << right_size << ", " << remaining_comps - left_comps << ")" << std::endl;
      }

    }

    if (break_flag) break;
  }
}

void print_vec(const std::vector<int>& vec) {
  for (int num: vec)
    std::cout << num << " ";
  std::cout << std::endl;
}

int main() {
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    MemoMap memo;

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string lc_temp;
        getline(cin, lc_temp);

        vector<string> lc = split_string(lc_temp);

        int l = stoi(lc[0]);
        int c = stoi(lc[1]);

        if (!can_make_array(l, c)) {
          std::cout << -1 << std::endl;
          continue;
        }

        long long l_real = l, c_real = c;
        //std::vector<int> arr = gen_array(l_real, c_real, memo);

        std::vector<int> arr(l_real);
        for (int x = 0; x < l_real; ++x) arr[x] = x + 1;

        gen_array2(arr, 0, l_real - 1, c_real, memo);
        int actual_comparisons = lena_sort(arr);
        if (actual_comparisons != c) {
          std::cout << "ERROR: Generated array yielded "
                    << actual_comparisons <<
                    " comparisons instead of the expected "
                    << c << std::endl;
        }

        print_vec(arr);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
