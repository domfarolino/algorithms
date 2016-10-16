#include <string>
#include <iostream>
#include <functional>

#include "autoKey.h"

int mod26(int a) {
  int b = 26;
  int r = a % b;
  return r < 0 ? r + b : r;
}

std::string updateText(const std::string &text,
                       std::function<char(char, int)> func) {
  std::string result;
  char letter;
  for (unsigned int i = 0; i < text.size(); i++) {
    letter = std::toupper(text[i]);
    result += std::isalpha(letter) ? func(letter, i) : letter;
  }
  return result;
}

std::string encrypt(const std::string &text, const std::string &key) {
  return updateText(text, [&key](char letter, int i) {
    return mod26(((int)letter) + ((int)key[i])) + 65;
  });
}

std::string decrypt(const std::string &text, const std::string &key) {
  return updateText(text, [&key](char letter, int i) {
    return mod26(((int)letter) - ((int)key[i])) + 65;
  });
}
