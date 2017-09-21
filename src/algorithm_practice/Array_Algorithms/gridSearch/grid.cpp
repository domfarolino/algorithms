#include <iostream>
#include <string>
#include <vector>

// Source: https://www.hackerrank.com/challenges/the-grid-search

/**
 * Grid Search
 * Without going into too much detail (problem description found above)
 * the idea of this algorithm is to mimic Ctrl-F for a grid. Basically
 * you take two grids G and P and indicate whether or not P exists
 * inside G. The way I thought of this is as follows. It is obvious
 * we want to iterate character by character through G to search for
 * the existence of P however before we can/should iterate we probably
 * want to check some basic edge cases that we could catch quickly. First
 * off we know that if the size of P > G then we can automatically return
 * false. Also if P's size is 0 we can return true. Note this is a high
 * level overview of the edges - see the code below for exact details.
 *
 * Now for the actual iterating. The idea is we should check each character
 * of the G grid to see if the grid P starts at this character. Note we should
 * figure out the boundaries of G we should traverse by looking at an example.
 * Consider G being of 4 rows and 4 columns and P 3 rows and 3 columns. It should
 * be clear that we should never search for P after the second row or second column
 * of G and this makes sense. So what we can we use to resolve the boundaries?
 * r = 0; r <= gRows - pRows or r < gRows - pRows + 1
 * c = 0; c <= gCols - pCols or c < gCols - pCols + 1
 *
 * These make sense if you run through a couple of examples by hand. After this we
 * can be assured that we can check the full length of grid P without running off
 * a row or column in G. This is a nice promise we've made ourselves (yay) and now
 * we just need to figure out given some starting point in G (r, c) if P exists.
 *
 * There are a couple ways to do this. First, we could iterate through all of P
 * starting at (pRow = 0, pCol = 0) of P checking if P[pRow][pCol] == G[r + pRow][c + pCol].
 * It is intuitive and easy since we know that iterating through all of P will never
 * run us off of the end of a G row or col (yay promise).
 *
 * The exact opposite way to do this would be to iterate through G starting at a
 * given position (r, c). We can keep track the current position we're at in G with
 * gRow, gCol which init = (r, c). We only want to go while gRow < r + pRows and gCol + pCols
 * so we don't go farther than we need to in G. For example if we start at (1, 1) in G
 * and P only has 1 row and 1 column, we only want to check 1 row and 1 column of G.
 * Now when indexing in P we need to work backwards a bit. We've put our gRow and gCol
 * in terms of r and pRows, and c + pCols respectively. This means
 * P[0][0] = P[gRow - r][gCol - c].
 *
 * Complexity analysis:
 * Time complexity: O(gR*gC + pR*pC) = O(gR*gC)
 * Space complexity: O(1) (no extra data besides input)
 *
 * Note the below algorithm is designed to work with a vector of strings where each
 * string is a row of characters. Strings are part of the STL so really not much of
 * the API we're using would change if we utilized nested vectors instead. Strings
 * are essentially arrays are essentially vectors are essentially lit.
 */

bool checkGridEquivalence(std::vector<std::string>& haystack, std::vector<std::string>& needle, int rows, int cols) {
  for (int r = rows; r < rows + needle.size(); ++r) {
    for (int c = cols; c < cols + needle[0].length(); ++c) {
      if (haystack[r][c] != needle[r - rows][c - cols]) return false;
    }
  }

  return true;
}

bool gridExists(std::vector<std::string>& haystack, std::vector<std::string>& needle) {
  if ((!haystack.size() && !needle.size()) || !needle.size()) return true;
  if (needle.size() > haystack.size() || needle[0].size() > haystack[0].size()) return false;

  for (int r = 0; r < haystack.size() - needle.size() + 1; ++r) {
    for (int c = 0; c < haystack[0].size() - needle[0].length() + 1; ++c) {
      if (checkGridEquivalence(haystack, needle, r, c)) return true;
    }
  }

  return false;
}

int main() {
  int t, gR, gC, pR, pC;
  std::vector<std::string> G, P;
  std::cin >> t;

  // Main driver
  for (int i = 0; i < t; ++i) {
    std::cin >> gR >> gC;
    G.resize(gR);

    // Fill G
    for (int j = 0; j < gR; ++j) {
      std::cin >> G[j];
    }

    std::cin >> pR >> pC;
    P.resize(pR);

    // Fill P
    for (int j = 0; j < pR; ++j) {
      std::cin >> P[j];
    }

    // Get some answers
    (gridExists(G, P)) ? std::cout << "YES" : std::cout << "NO";
    std::cout << std::endl;

    G.clear();
    P.clear();
  }

  return 0;
}
