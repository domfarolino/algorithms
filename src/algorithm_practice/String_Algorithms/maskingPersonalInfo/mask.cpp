#include <iostream>
#include <string>

// Source: https://leetcode.com/contest/weekly-contest-83/problems/masking-personal-information/

/**
 * Masking Personal Information
 * It makes sense to split this problem into two distinct solutions: one for emails,
 * one for phone numbers. Let's tackle them separately:
 *
 * Phone numbers
 * We know that the phone number string has anywhere from 10-13 digits, and
 * potentially a myriad of interlaced random unimportant symbols. The resulting
 * string we want to return will always have ***-***-NNNN, where the |NNNN| is the
 * last four digits appearing in the number string. Optionally if there are additional
 * numbers in the front, they will comprise a country code anywhere from 1-3 characters,
 * and we'd append +YYY- to the string above ^. Since the second "half" of the string is
 * always guaranteed to have that specific format, I figured it'd make sense to build the
 * return string in reverse, and flip it around before returning.
 * 1.) Get the number of digits appearing in the phone number string (we'll need this # later)
 * 2.) Add the last four digits of the phone number (reverse order) string (easier to do this from back-to-front)
 * 3.) Append "-***-***" (this is reverse of ***-***-)
 * 4.) If # digits > 10, add:
 *     a.) "-"
 *     b.) Appropriate number of "*"s, for size of country code (1, 2, or 3)
 *     c.) "+"
 * 5.) Reverse and return the string!
 *
 * Complexity analysis:
 * Time complexity: O(n) (# digits will be between 10-13, but we can have arbitrarily large number of random symbols)
 * Space complexity: O(1)
 *
 * Emails
 * IMO the email case is slightly simpler. Basically we need to:
 * 1.) Lower-case the entire string
 * 2.) Build the masked version of name1 (everything before "@")
 * 3.) Concat masked version of name1 with everything from the "@" => end of original string
 *
 * To carry out (2) there are several ways. The easiest to me seems to create a string of 7 "*"s, and simply
 * replace the first character with the first character of the now-lower-case email string, and the last character
 * with the character appearing right before the "@" symbol.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

std::string maskPhoneNumber(const std::string& s) {
  std::string returnString;
  int numDigits = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') numDigits++;
  }

  // Add the last 4 digits in reverse order
  int i = s.length() - 1;
  while (i >= 0 && returnString.length() < 4) {
    if (s[i] >= '0' && s[i] <= '9') returnString.append(1, s[i]);
    i--;
  }

  returnString.append("-***-***");

  if (numDigits > 10) {
    returnString.append(1, '-');
    returnString.append(numDigits - 10, '*');
    returnString.append(1,'+');
  }

  std::reverse(returnString.begin(), returnString.end());
  return returnString;
}

std::string maskEmail(std::string s) {
  std::string returnString;

  // Lowercase the whole string
  for (int i = 0; i < s.length(); ++i) s[i] = std::tolower(s[i]);

  returnString.append(7, '*'); // *******
  returnString[0] = s[0]; // x******

  int atSymbolPos = s.find('@');
  returnString[6] = s[atSymbolPos - 1];
  returnString.append(s, atSymbolPos, std::string::npos);
  return returnString;
}

std::string maskPII(const std::string& s) {
  std::string returnString;
  if (s.find('@') == std::string::npos)
    return maskPhoneNumber(s);
  else
    return maskEmail(s);
}

int main() {
  std::string returnString = maskPII("86--+(-)++6305-29434");
  std::cout << returnString << std::endl;

  returnString = maskPII("doM@chromIum.ORg");
  std::cout << returnString << std::endl;
  return 0;
}
