#include <iostream>
#include <string>
#include <algorithm>

// Caesar Cipher
//
// Simple and most widely known encryption of the encryption techniques.
//
// Encryption: E(x) = (x + n) mod 26
// Decryption: D(x) = (x - n) mod 26
//
// Each character in a phrase is shifted by a number. Originally


int mod(int a, int b) {
  int remainder = a%b;
  return remainder < 0 ? remainder + b : remainder;
}

void updateCipher(std::string &cipher, std::function<char(char)> func) {
  char character;
  for (int i = 0; i < cipher.length(); i++) {
    character = std::toupper(cipher[i]);
    cipher[i] = std::isalpha(character) ? func(character) : character;
  }

  // clean up whitespaces in the string
  cipher.erase(
      std::remove_if(cipher.begin(), cipher.end(),
        [](char x) { return std::isspace(x); }), cipher.end());
}

void encrypt(std::string &cipher, int shiftAmount) {
  auto encryptFunction = [&shiftAmount](char letter) {
    return mod(((int)letter - 65) + shiftAmount, 26) + 65;
  };

  updateCipher(cipher, encryptFunction);
}

void decrypt(std::string &cipher, int shiftAmount) {
  auto decryptFunction = [&shiftAmount](char letter) {
    return mod(((int)letter - 65) - shiftAmount, 26) + 65;
  };

  updateCipher(cipher, decryptFunction);
}

void testEncryption(std::string &example, int shiftAmount){
  std::cout << "Encrypting: " << example << " shifted: " << shiftAmount << " = ";
  encrypt(example, shiftAmount);
  std::cout << example << std::endl;
}

void testDecryption(std::string &example, int shiftAmount){
  std::cout << "Decrypting: " << example << " shifted: " << shiftAmount << " = ";
  decrypt(example, shiftAmount);
  std::cout << example << std::endl;
}

int main(int argc, char *argv[])
{
  // general encryption and decryption tests
  std::string example = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  testEncryption(example, 3);    //DEFGHIJKLMNOPQRSTUVWXYZABC

  std::string example2 = "ATTACKATDAWN";
  testEncryption(example2, 5);   // FYYFHPFYIFBS

  std::string example3 = "DEFGHIJKLMNOPQRSTUVWXYZABC";
  testDecryption(example3, 3);   // ABCDEFGHIJKLMNOPQRSTUVWXYZ

  std::string example4 = "FYYFHPFYIFBS";
  testDecryption(example4, 5);   // ATTACKATDAWN

  std::string exampleEdgeCase1 = "Test With Spaces and Capitals";
  testEncryption(exampleEdgeCase1, 23);  // QBPQ TFQE PMXZBP XKA ZXMFQXIP
  testDecryption(exampleEdgeCase1, 23);

  std::string exampleEdgeCase2 = "T3$T w1th Numb3rS & $ymB0ls";
  testEncryption(exampleEdgeCase2, 123);  // QBPQ TFQE PMXZBP XKA ZXMFQXIP
  testDecryption(exampleEdgeCase2, 123);

  // solve using chi-squared
}
