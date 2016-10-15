#include <iostream>
#include <iomanip>
#include <math.h>

#include "cryptoAnalysis.h"
#include "caesarCipher.h"

// Crytoanalysis Breaking the code
// Caesar cipher is a perfect example of how insecure it is.
// This cipher can be broken simply through cryptanalysis. Cryptanalysis is the art of
// breaking codes and ciphers. In the English language, there is a very distinct distribution
// that helps crack the code. For instance, 'e' is the most common letter and it appears almost
// 13% of the time. 'z' is the least common letter and appears 1% of the time.

chiSquaredResult_t calculateBestResult(const results_t& results) {
  auto bestResult = results[0];
  for (auto it = results.begin(); it != results.end(); it++) {
    if (std::get<2>(bestResult) > std::get<2>(*it)) {
      bestResult = *it;
    }
  }
  return bestResult;
}

void printResults(const results_t& results) {
  auto bestResult = calculateBestResult(results);
  std::cout << std::setw(10) << "Offset" << std::setw(20) << "Encrypted string" << std::setw(27) << "chi squared" << std::endl;
  for (auto it = results.begin(); it != results.end(); it++) {
    std::cout << std::setw(10) << std::get<0>(*it) << std::setw(30)
      << std::get<1>(*it).substr(0,26) << "..." << std::setw(14)
      << std::get<2>(*it) << std::endl;
  }

  std::cout << std::endl << "Chi Squared analysis determined that " << std::get<1>(bestResult) << " with a score of: "
    << std::get<2>(bestResult) << " and an offset of: " << std::get<0>(bestResult) << std::endl;
}

void clearFrequencyList(std::vector<int>& frequencyList) {
    if (frequencyList.size() > 0) {
      frequencyList.clear();
    }

    for (int i = 0; i < 26; i++) {
      frequencyList.push_back(0);
    }
}

void buildFrequencyList(std::vector<int>& frequencyList, const std::string& cipher) {
  // Count the frequencies of characters into an array
  // index 0: A through index 25: Z
  for (unsigned int i = 0; i < cipher.size(); i++) {
    frequencyList[cipher[i] - 65]++;
  }
}

void initializeFrequencyList(std::vector<int>& frequencyList, const std::string& encryptedCipher) {
    clearFrequencyList(frequencyList);
    buildFrequencyList(frequencyList, encryptedCipher);
}

float calculateChiSquaredFromCipher(const std::string& encryptedCipher, const std::vector<int>& frequencyList) {
    float chiSquaredSum = 0;
    int totalCount = encryptedCipher.size();
    for (int i = 0; i < 26; i++) {
      float letterFrequency = englishFrequencyList[i];
      chiSquaredSum += pow(frequencyList[i] - (totalCount * letterFrequency), 2) / (totalCount * letterFrequency);
    }
    return chiSquaredSum;
}

void performChiSquaredAnalysis(const std::string& cipher) {
  float chiSquaredSum;
  std::vector<int> frequencyList;
  results_t chiSquaredResults;
  for (int i = 0; i < 26; i++) {
    std::string encryptedCipher = encrypt(cipher, i);
    initializeFrequencyList(frequencyList, encryptedCipher);
    chiSquaredSum = calculateChiSquaredFromCipher(encryptedCipher, frequencyList);
    chiSquaredResults.push_back(std::make_tuple(i, encryptedCipher, chiSquaredSum));
  }
  printResults(chiSquaredResults);
}

