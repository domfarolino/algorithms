#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <string>
#include <functional>

std::string updateCipher(std::string, const std::function<char(char)>);

std::string encrypt(const std::string, const int&);

std::string decrypt(const std::string, const int&);

void testEncryption(const std::string, const int&);

void testDecryption(const std::string, const int&);

#endif /* CAESAR_CIPHER_H */

