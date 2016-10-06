#include <iostream>
#include <string>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=386
// uDebug: https://www.udebug.com/UVa/445 <= currently there's an error

/**
 * Marvelous Mazes
 * This is much more of a coding problem
 * than a problem solving one, so the theory
 * is pretty simple.
 */

int main() {
  string mazeData;
  int currentRepeat = 0;

    while (getline(cin, mazeData)) {
      
      for (int i = 0; i < mazeData.length(); ++i) {
      
        if (mazeData[i] >= 'A' && mazeData[i] <= 'Z' || mazeData[i] == 'b' || mazeData[i] == '*') { // A-Z || b || *
          while (currentRepeat) {
            if (mazeData[i] == 'b') cout << ' ';
            else cout << mazeData[i];
            currentRepeat--;
          }
        } else if (mazeData[i] == '!') { // !
          cout << endl;
        } else if (mazeData[i] >= '0' && mazeData[i] <= '9') { // 0-9
          currentRepeat += mazeData[i]-'0';
        }
      
      }

      cout << endl;

    }

  
  return 0;
}