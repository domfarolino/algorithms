#include <iostream>
#include <string>

#include "autoKey.h"

// Autokey Cipher is a polyalphabetic substitution cipher.
//
// It is closely related to the Vigenere Cipher, but uses a different
//  method of generating the key.
//
// It was invented by Blaise de Vigenere in 1586 and is generally
//  more secure than the vigenere cipher. The reason why it is more secure
//  than vigenere cipher is that autokey cipher doesn't use repeating keys;
//  therefore, Index of Coincidence doesn't work which made it easy to solve
//  the vigenere cipher.
//
// The autokey cipher can be cracked by measuring fitness based on
// quadgram statistics.
//
// To encipher a message, take a desired string to be the key. The key is then
//  appended with the plain text.
//
// Given FORTIFICATION as the key
//
// key:  FORTIFICATIONDEFENDTHEEASTWA
// text: DEFENDTHEEASTWALLOFTHECASTLE
//

std::string buildKey(const std::string &text, const std::string &key) {
  return (key+text).substr(0, text.size());
}

void test(std::string plainText, std::string key){
  std::string autokey = buildKey(plainText, key);
  std::string encryptedString = encrypt(plainText, autokey);
  std::cout << "autokey: \t" << autokey << std::endl;
  std::cout << "text: \t\t"  << plainText << std::endl;
  std::cout << "encrypted: \t" << encrypt(plainText, autokey) << std::endl;
  std::cout << "decrypted: \t" << decrypt(encryptedString, autokey)
    << std::endl;
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "---------------" << std::endl;
  std::cout << "Auto Key Cipher" << std::endl;
  std::cout << "---------------" << std::endl;

  test("DEFENDTHEEASTWALLOFTHECASTLE", "FORTIFICATION");
  test("ATTACKATDAWN", "DEFENSE");
  test("SEEKMEATMIDNIGHT", "SLIENT");
  test("HUNTINGBEGINSATDAWN", "GIVER");
}
