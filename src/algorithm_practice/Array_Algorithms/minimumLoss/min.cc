#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

// Hackerrank-provided.
std::vector<std::string> split_string(std::string input_string) {
  std::string::iterator new_end = std::unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
    return x == y and x == ' ';
  });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  std::vector<std::string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != std::string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));
  return splits;
}

// Complete the minimum_loss function below.
long minimum_loss(const std::vector<long>& prices) {
  std::set<long> vals;
  long min_difference = LONG_MAX;
  std::set<long>::iterator it;
  for (const long& price: prices) {
    it = vals.insert(price).first;
    if (++it == vals.end())
      continue;

    // Update |min_difference| if necessary.
    min_difference = std::min(min_difference, *it - price);
  }

  // Assert: |min_difference| != LONG_MAX;
  return min_difference;
}

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string price_temp_temp;
  getline(std::cin, price_temp_temp);

  std::vector<std::string> price_temp = split_string(price_temp_temp);

  std::vector<long> price(n);

  for (int i = 0; i < n; i++) {
    long price_item = stol(price_temp[i]);
    price[i] = price_item;
  }

  long result = minimum_loss(price);
  std::cout << result << std::endl;
  return 0;
}
