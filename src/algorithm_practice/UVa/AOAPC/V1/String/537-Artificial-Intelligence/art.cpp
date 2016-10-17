#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=478

/**
 * Artificial Intelligence
 * It is possible to build this algorithm to be more robust
 * than is necessary, such that it can easily be adapted to suit
 * a problem with a variable amount of data fields and calculations.
 * This could be done by scanning through the string and pulling out
 * and pairing up calculations however in this case all we really need
 * to do is take advantage of string::find and look for two equal signs,
 * pull the data fields out and through a little bit of logic we output the
 * correct answer. Theory and coding challenge in this problem are very simple.
 */

/**
 * This helper function takes in a string
 */
double fillOutNumber(const string& pool, int pos) {
  int i = pos;
  string numString = "";
  double returnNumber;

  while ((pool[i] >= '0' && pool[i] <= '9') || pool[i] == '.' || pool[i] == '-') {
    numString += pool[i];
    ++i;
  }

  if (pool[i] == 'm') {
    returnNumber = stod(numString)/1000.0;
  } else if (pool[i] == 'k') {
    returnNumber = stod(numString)*1000.0;
  } else if (pool[i] == 'M') {
    returnNumber = stod(numString)*1000000.0;
  } else {
    returnNumber = stod(numString);
  }

  return returnNumber;
}

int main() {
  int total;
  string problemStatement;

  // All data field information
  int dataFieldPosition;
  bool hasP, hasI, hasU;
  double P, I, U;

  cin >> total;
  cin.ignore();

  cout << fixed << setprecision(2);

  for (int i = 0; i < total; ++i) {
    dataFieldPosition = -1;
    hasP = false, hasI = false, hasU = false;

    cout << "Problem #" << i+1 << endl;
    getline(cin, problemStatement);

    // Get the position of each data field "=" sign
    for (int j = 0; j < 2; ++j) {
      dataFieldPosition = problemStatement.find("=", dataFieldPosition+1);

      if (problemStatement[dataFieldPosition-1] == 'P') {
        hasP = true;
        P = fillOutNumber(problemStatement, dataFieldPosition+1);
      } else if (problemStatement[dataFieldPosition-1] == 'U') {
        hasU = true;
        U = fillOutNumber(problemStatement, dataFieldPosition+1);
      } else if (problemStatement[dataFieldPosition-1] == 'I') {
        hasI = true;
        I = fillOutNumber(problemStatement, dataFieldPosition+1);
      }
    }

    if (!hasP) cout << "P=" << I*U << "W";
    if (!hasI) cout << "I=" << P/U << "A";
    if (!hasU) cout << "U=" << P/I << "V";

    cout << endl << endl;
  }

  return 0;
}
