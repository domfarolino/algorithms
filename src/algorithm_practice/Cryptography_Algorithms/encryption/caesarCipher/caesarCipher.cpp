#include <iostream>
#include <string>
#include <functional>

#include "caesarCipher.h"

// Caesar Cipher, (ROT13 encription, which uses an offset of 13)
//
// Simple and most widely known encryption of the encryption techniques.
// Caesar cipher is a substitution cipher where each letter in plain text
//  is 'shifted' a certain number of letters in the alphabet.
//  This cipher offers no communication security and can easily be broken
//  by pen and paper
//
// Encryption: E(x) = (x + n) mod 26
// Decryption: D(x) = (x - n) mod 26
//

int mod(int a, int b) {
  int r = a % b;
  return r < 0 ? r + b : r;
}

std::string updateCipher(std::string cipher,
                         const std::function<char(char)> func) {
  char character;
  for (unsigned int i = 0; i < cipher.length(); i++) {
    character = std::toupper(cipher[i]);
    cipher[i] = std::isalpha(character) ? func(character) : character;
  }
  return cipher;
}

std::string encrypt(const std::string cipher, const int& shiftAmount) {
  return updateCipher(cipher, [&shiftAmount](char letter) {
    return mod(((int)letter - 65) + shiftAmount, 26) + 65;
  });
}

std::string decrypt(const std::string cipher, const int& shiftAmount) {
  return updateCipher(cipher, [&shiftAmount](char letter) {
    return mod(((int)letter - 65) - shiftAmount, 26) + 65;
  });
}

void testEncryption(const std::string cipher, const int& shiftAmount){
  std::cout << "Encrypting: \n\t\"" << cipher << "\" shifted: "
    << shiftAmount << std::endl;
  std::string encryptedCipher = encrypt(cipher, shiftAmount);
  std::cout << "\t\"" << encryptedCipher << "\"" << std::endl;
}

void testDecryption(const std::string cipher, const int& shiftAmount){
  std::cout << "Decrypting: \n\t\"" << cipher << "\" shifted: "
    << shiftAmount << std::endl;
  std::string decryptedCipher = decrypt(cipher, shiftAmount);
  std::cout << "\t\"" << decryptedCipher << "\"" << std::endl;
}
