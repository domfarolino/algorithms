#include <iostream>

// Source: ACM ICPC 2018

bool harshad(long in) {
  long saveIn = in;
  int sum = 0;
  while (in) {
    sum += in % 10;
    in /= 10;
  }

  return (saveIn % sum == 0);
}

int main() {
  long input;
  std::cin >> input;

  while (!harshad(input))
    input++;

  std::cout << input << std::endl;
  return 0;
}
