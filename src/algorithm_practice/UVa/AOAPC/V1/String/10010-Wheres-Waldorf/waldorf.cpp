#include <iostream>
#include <string>
#include <utility> // std::pair

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=951

/**
 * Where's Waldorf
 * This file contains a solution, and several
 * modified versions of the solution to work in
 * a broader range of cases.
 */

/**
 * Below is a function to tell if a word can be found at a given position in a grid
 * via brute force DFS. This function assumes a word does not have to be arranged in
 * a straight uninterrupted path. This in turn treats the grid as a true graph/tree which
 * is useful for path finding but will certainly not yield the correct answer for this OJ.
 */
pair<int, int> foundWordDFS(const string& word, string* grid, int rows, int cols, int r, int c, int progress) {
  if (progress == word.length()) return make_pair(r, c);
  if (r >= rows || r < 0 || c >= cols || c < 0 || grid[r][c] != word[progress]) return make_pair(-1, -1);

  int r_moves[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int c_moves[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  pair<int, int> tmpPair;

  for (int i = 0; i < 8; ++i) {
    tmpPair = foundWordDFS(word, grid, rows, cols, r+r_moves[i], c+c_moves[i], progress+1);
    if (tmpPair.first != -1 && tmpPair.second != -1) return make_pair(r, c);
  }
}

/**
 * Below is a failed attempt at an iterative solution to tell if a given word
 * can be found at a given position. This function assumes a word does not have
 * to be arranged in a straight uninterrupted path. To get this solution working
 * we need to implement something more along the lines of BFS tree traversal. This
 * fails because it goes down the first path that matches the next character and if
 * that path doesn't pan out correctly, we give up. Instead we need to maintain some
 * queue of next paths that match the next character and only give up when that queue
 * is empty and the entire string `word` has not been matched.
 */
pair<int, int> foundWordIterativeFail(const string& word, string* grid, int rows, int cols, int r, int c) {
  if (r >= rows || r < 0 || c >= cols || c < 0 || grid[r][c] != word[0]) return make_pair(-1, -1);
  int r_moves[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int c_moves[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  int tmpR = r, tmpC = c, move;

  for (int i = 1; i < word.length(); ++i) {

    move = 0;
    while (move < 8) {
      if (tmpR+r_moves[move] < rows && tmpR+r_moves[move] >= 0 && tmpC+c_moves[move] < cols && tmpC+c_moves[move] >= 0 && grid[tmpR+r_moves[move]][tmpC+c_moves[move]] == word[i]) {
        tmpR += r_moves[move];
        tmpC += c_moves[move];
        break;
      }
      
      move++;
    }

    if (move == 8) {
      r = -1;
      c = -1; // these ensure that we return a falsy pair
      break;
    }
  }

  return make_pair(r, c);
}

/**
 * The actual quality a word must meet in this challenge is that the word must
 * exist in a straight uninterrupted path. This solution can tell whether a word
 * exists in a grid given some position by traveling outward in one of 8 directions
 * and then maintaining only that direction. This is a lot simpler as it turns the problem
 * into less of a path finding one. Since we only have 8 options and must stick with that option
 * for every subsequent character extension in the grid this makes allows our outer for loop to be
 * managed by the constant factor 8, as we can try committing to each direciton until either some
 * boundaries are crossed meaning the current path failed, characters no longer match also meaning the
 * current path failed, or we've fully covered the word in which case we want to break from every loop
 * and return an pair<int, int> indicating that the word has been found at position r,c.
 *
 * This brute force solution has a time complexity of O(m*n*l) where m = rows, n = cols, and l = length of
 * word to find. The space complexity of this algorithm is O(1).
 */
pair<int, int> foundWord(const string& word, string* grid, int rows, int cols, int r, int c) {
  if (word[0] != grid[r][c]) return make_pair(-1, -1);
  int r_moves[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int c_moves[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  int tmpR, tmpC, progress;

  for (int i = 0; i < 8; ++i) {

    tmpR = r;
    tmpC = c;
    progress = 1;

    while (tmpR+r_moves[i] >= 0 && tmpR+r_moves[i] < rows && tmpC+c_moves[i] >=0 && tmpC+c_moves[i] < cols && grid[tmpR+r_moves[i]][tmpC+c_moves[i]] == word[progress] && progress < word.length()) {
      tmpR += r_moves[i];
      tmpC += c_moves[i];
      progress++;
    }

    if (progress == word.length()) break;
  }

  if (progress == word.length()) return make_pair(r, c);
  else return make_pair(-1, -1);
}

/**
 * O(n) algorithm to make an input string all lowercase
 * by taking advantage of ascii value placement
 */
void toLower(string& inputString) {
  for (int i = 0; i < inputString.length(); ++i) {
    if (inputString[i] <= 'Z' && inputString[i] >= 'A') inputString[i] += 32;
  }
}

int main() {
  int total, rows, cols, numWords;
  string *grid, *words;
  pair<int, int> pairToEvaluate;
  bool shouldContinueToNextWord;

  cin >> total;

  for (int i = 0; i < total; ++i) {
    cin >> rows >> cols;

    // Allocate grid
    grid = new string[rows];

    // Fill up grid
    for (int r = 0; r < rows; ++r) {
      cin >> grid[r];
      toLower(grid[r]);
    }

    // Grab number of words
    cin >> numWords;

    // Allocate words array
    words = new string[numWords];

    // Fill out words array
    for (int w = 0; w < numWords; ++w) {
      cin >> words[w];
      toLower(words[w]);
    }

    // Guts of algorithm below here
    for (int w = 0; w < numWords; ++w) {

      shouldContinueToNextWord = false;

      for (int r = 0; r < rows; ++r) {

        for (int c = 0; c < cols; ++c) {
          pairToEvaluate = foundWord(words[w], grid, rows, cols, r, c);
          if (pairToEvaluate.first != -1 && pairToEvaluate.second != -1) {
            cout << pairToEvaluate.first+1 << " " << pairToEvaluate.second+1 << endl;
            shouldContinueToNextWord = true;
            break;
          }
        } // cols

        if (shouldContinueToNextWord) break;

      } // rows

      if (!shouldContinueToNextWord) cout << "Shit, didn't find " << words[w] << " at all" << endl;
    
    } // words

    // Deallocate entire grid and words array
    delete[] grid;
    delete[] words;

    if (i != total-1) cout << endl; // OJ

  }
  
  return 0;
}


/**
 * Below are the very beginnings of a c-style solution
 */

// #include <iostream>

// using namespace std;

// int main() {
//   int total, rows, cols;
//   char **grid;

//   cin >> total;

//   for (int i = 0; i < total; ++i) {
//     cin >> rows >> cols;

//     // Allocate and fill out grid
//     grid = new char*[rows];
//     for (int r = 0; r < rows; ++r) grid[r] = new char[cols];

//     // Fill up grid
//     for (int r = 0; r < rows; ++r) {
//       for (int c = 0; c < cols; ++c) {
//         cin >> grid[r][c];
//       }
//     }

//     // Diagnostic: print grid
//     for (int r = 0; r < rows; ++r) {

//       for (int c = 0; c < cols; ++c) {
//         cout << grid[r][c];
//       }

//       cout << endl;
    
//     }

//     // Deallocate entire grid
//     for (int r = 0; r < rows; ++r) delete[] grid[r];
//     delete[] grid;

//   }
  
//   return 0;
// }