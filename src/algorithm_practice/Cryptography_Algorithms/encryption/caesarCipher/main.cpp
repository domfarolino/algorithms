#include <string>
#include <iostream>
#include "caesarCipher.h"
#include "cryptoAnalysis.h"

int main(int argc, char *argv[])
{
  // general encryption and decryption tests
  std::cout << "-------------" << std::endl;
  std::cout << "Caesar Cipher" << std::endl;
  std::cout << "-------------" << std::endl;
  std::string example = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  testEncryption(example, 3);    //DEFGHIJKLMNOPQRSTUVWXYZABC

  std::string example2 = "ATTACKATDAWN";
  testEncryption(example2, 5);   // FYYFHPFYIFBS

  std::string example3 = "DEFGHIJKLMNOPQRSTUVWXYZABC";
  testDecryption(example3, 3);   // ABCDEFGHIJKLMNOPQRSTUVWXYZ

  std::string example4 = "FYYFHPFYIFBS";
  testDecryption(example4, 5);   // ATTACKATDAWN

  std::string exampleEdgeCase1 = "Test With Spaces and Capitals";
  testEncryption(exampleEdgeCase1, 23);  // QBPQTFQEPMXZBPXKAZXMFQXIP
  testDecryption(exampleEdgeCase1, 23);

  std::string exampleEdgeCase2 = "T3$T w1th Numb3rS & $ymB0ls";
  testEncryption(exampleEdgeCase2, 123);
  testDecryption(exampleEdgeCase2, 123);

  // solve using chi-squared
  std::cout
    << "------------------------------------------" << std::endl
    << "Solve via chi-squared statistical analysis" << std::endl
    << "------------------------------------------" << std::endl;

  std::vector<std::string> testCiphers {
    "FYYFHPFYIFBS", "QBPQ TFQE PMXZBP XKA ZXMFQXIP!",
    "AOLJHLZHYJPWOLYPZVULVMAOLLHYSPLZARUVDUHUKZPTWSLZAJPWOLYZPAPZHAFWLVMZBIZA"
    "PABAPVUJPWOLYPUDOPJOLHJOSLAALYPUAOLWSHPUALEAPZZOPMALKHJLYAHPUUBTILYVMWSH"
    "JLZKVDUAOLHSWOHILA"
  };

  for (auto it = testCiphers.begin(); it != testCiphers.end(); it++){
    performChiSquaredAnalysis(*it);
  }

}
