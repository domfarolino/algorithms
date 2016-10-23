#include <iostream>
#include <string>
#include <math.h> /* floor */

/*
 * Palindrome checker
 *
 * Write code to check if a string is palindrome or not?
 *
 * A string is a palindrome if the string is the same
 *  whether spelled forwards or backwards
 */

std::string isPalindrome(std::string text) {
  // remove non alphabetic characters
  std::string newText;
  for (int i = 0; i < text.size(); i++) {
    if (std::isalpha(text[i])) {
      newText += std::tolower(text[i]);
    }
  }

  // check if a string is a palindrome.
  // Only check half of the array instead of the whole string
  for (int i = 0; i < floor(newText.size() / 2) + 1; i++) {
    if (newText[i] != newText[newText.size() - i - 1]) {
      return "False";
    }
  }
  return "True";
}

void test(std::string text) {
  std::cout << text << ": " << isPalindrome(text) << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "palindrome tests" << std::endl;
  test("racecar");
  test("r a c e c a r!");
  test("Mother Eve's noose we soon sever, eh Tom?");
  test("On a clover, if alive, erupts a vast, pure evil; a fire volcano.");

  std::cout << "Non-palindrome tests" << std::endl;
  test("abcd");
  test("palindrome");
  test("!!hacktoberfest!!");
  return 0;
}
