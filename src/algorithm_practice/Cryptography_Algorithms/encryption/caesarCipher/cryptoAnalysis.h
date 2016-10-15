#ifndef CRYPTO_ANALYSIS_H
#define CRYPTO_ANALYSIS_H

#include <string>
#include <vector>
#include <tuple>

typedef std::tuple<int, std::string, float> chiSquaredResult_t;
typedef std::vector<chiSquaredResult_t> results_t;

const std::vector<float> englishFrequencyList {
    .0855,   /* A */
    .0160,   /* B */
    .0316,   /* C */
    .0387,   /* D */
    .1210,   /* E */
    .0218,   /* F */
    .0209,   /* G */
    .0496,   /* H */
    .0733,   /* I */
    .0022,   /* J */
    .0081,   /* K */
    .0421,   /* L */
    .0253,   /* M */
    .0717,   /* N */
    .0747,   /* O */
    .0207,   /* P */
    .0010,   /* Q */
    .0633,   /* R */
    .0673,   /* S */
    .0894,   /* T */
    .0268,   /* U */
    .0106,   /* V */
    .0183,   /* W */
    .0019,   /* X */
    .0172,   /* Y */
    .0011,   /* Z */
};

chiSquaredResult_t calculateBestResult(const results_t&);

void printResults(const results_t&);

void clearFrequencyList(std::vector<int>&);

void buildFrequencyList(std::vector<int>&, const std::string&);

void initializeFrequencyList(std::vector<int>&, const std::string&);

float calculateChiSquaredFromCipher(const std::string&, const std::vector<int>&);

void performChiSquaredAnalysis(const std::string&);

#endif /* CRYPTO_ANALYSIS_H */
