#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=355

/**
 * Machined Surfaces
 * Description can be found in the source link. Key
 * realization in this problem is to think of input that
 * looks like this:
 *
 * |X     XXX|
 * |XX       |
 * |XXX   XXX|
 * |X      XX|
 *
 * as the following:
 *
 * |XXXX     |
 * |XX       |
 * |XXXXXX   |
 * |XXX      |
 *
 * Then to form a better picture of what is going on when
 * we bring the two machined surfaces together we can eliminate
 * as much whitespace on the right as we can:
 *
 * |XXXX  |
 * |XX    |
 * |XXXXXX|
 * |XXX   |
 *
 * The answer is then the amount of total whitespace in the above
 * image. It should be clear that the whitespace left in every row
 * after we tighten up our borders is dependent on the row with the
 * smallest amount of whitespace to begin with. In the end, this row
 * will have 0 spaces. The other rows will have o - min spaces left where
 * o = number of spaces originally in some row, and min = number of spaces
 * in the row with the minimum amount of whitespace. This makes sense because
 * when we move the right border over min spaces, we eliminate min spaces from
 * every row. So we could keep an integer value of the spaces appearing in each
 * row, find which one is the minimum, and then run our o - min for each row and
 * return the amount of spaces left.
 */

int numSpacesInRow(const string& row) {
  int numSpaces = 0;

  for (int i = 0; i < 24; ++i) {
    if (row[i] == ' ') numSpaces++;
  }

  return numSpaces;
}

int main() {
  int n, mini, spacesInRow, totalSpaces;
  string row = "";
  vector<int> v;

  while (cin >> n && n != 0) {
    v.reserve(n);
    mini = INT_MAX;
    totalSpaces = 0;
    
    for (int i = 0; i < n; ++i) {
      cin.get();
      getline(cin, row);
      spacesInRow = numSpacesInRow(row);
      mini = min(mini, spacesInRow);
      v.push_back(spacesInRow);
    }

    for (int i = 0; i < n; ++i) {
      totalSpaces += v[i] - mini;
    }

    cout << totalSpaces << endl;
    v.clear();
  }
  
  return 0;
}