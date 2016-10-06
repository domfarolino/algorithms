#include <iostream>
#include <string>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=398

/**
 * Linear Cellular Automata
 * This is a good problem to practice
 * breaking code out into different subroutines.
 * This is also a good exercise for dealing with
 * integers and characters and custom conversions
 * in the ASCII set.
 */

int charToVal(const char& character) {
  if (character == ' ') return 0;
  if (character == '.') return 1;
  if (character == 'x') return 2;
  if (character == 'W') return 3;
  else {
    cout << character << endl;
    return 65;
  }
}

char valToChar(const int& val) {
  if (val == 0) return ' ';
  if (val == 1) return '.';
  if (val == 2) return 'x';
  if (val == 3) return 'W';
  else {
    cout << val << endl;
    return 65;
  }
}

/**
 * The point of this function is to take a reference
 * to a string of bacteria and the DNA corresponding
 * to the bacteria and update the population of bacteria
 * based on the rules of their reproduction. The updated
 * value of some bacteria depends on the values of its neighbors.
 * They key to this function is realizing when we update some bacteria's
 * value and move onto the next bacteria, the next bacteria requires the
 * previous bacteria's value before it got updated, not its updated value.
 * This means we cannot just update some bacteria and move onto the next
 * one. Instead to solve this problem we can only update some bacteria once
 * we've saved the value of its original state. That way we can use this saved
 * state to update the next bacteria. More specifically we have a character in
 * the below implementation called oldChar to save the state of some bacteria before
 * we update it. Then when updating the next bacteria, we must consult oldChar instead
 * of the previous bacteria's new state.
 */
void updateBacteria(string& BACTERIA, int DNA[10]) {
  int k = 0;
  char oldChar = BACTERIA[0]; // used to save the state of some bacteria before updated

  // Handle first bacteria
  k = charToVal(oldChar) + charToVal(BACTERIA[1]);
  BACTERIA[0] = valToChar(DNA[k]);

  for (int i = 1; i < BACTERIA.size()-1; ++i) {
    k = charToVal(oldChar) + charToVal(BACTERIA[i]) + charToVal(BACTERIA[i+1]);
    oldChar = BACTERIA[i];
    BACTERIA[i] = valToChar(DNA[k]);
  }

  // Handle last bacteria
  k = charToVal(oldChar) + charToVal(BACTERIA[BACTERIA.size()-1]);
  BACTERIA[BACTERIA.size()-1] = valToChar(DNA[k]);
}

int main() {
  int total;

  cin >> total;

  int DNA[10];

  for (int i = 0; i < total; ++i) {

    string BACTERIA(40, ' ');
    BACTERIA[19] = '.';

    // Input all DNA elements
    for (int j = 0; j < 10; j++) cin >> DNA[j];
    
    for (int r = 0; r < 50; ++r) {

      for (int c = 0; c < 40; ++c) {
        cout << BACTERIA[c];
      }

      cout << endl;

      updateBacteria(BACTERIA, DNA);
    }

    if (i != total-1) cout << endl;
  }
  
  return 0;
}