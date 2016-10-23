#include <iostream>

/*
 * Fizz Buzz
 * The "Fizz-Buzz test" is an interview question designed to help filter out the
 * 99.5% of programming job candidates who can't seem to program their way out of
 * a wet paper bag.
 *
 * The text of the programming assignment is as follows:
 * "Write a program that prints the numbers from 1 to 100.
 * But for multiples of three print “Fizz” instead of the number
 *  and for the multiples of five print “Buzz”.
 * For numbers which are multiples of both three and five print “FizzBuzz”."
 *
 */
bool isDivisibleByX (int number, int divider) {
  return number % divider == 0;
}

int main(int argc, char *argv[])
{
  int maxRange;
  std::cout << "Input a range" << std::endl;
  std::cin >> maxRange;

  for (int i = 0; i < maxRange; i++) {
    std::cout << i << ": ";
    if (isDivisibleByX(i, 3)){
      std::cout << "fizz";
    }
    if (isDivisibleByX(i, 5)) {
      std::cout << "buzz";
    }

    std::cout << std::endl;
  }
}
