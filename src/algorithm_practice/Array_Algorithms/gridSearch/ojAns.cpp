// Source: https://www.hackerrank.com/challenges/the-grid-search
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool checkGridEquivalence(vector<string>& haystack, vector<string>& needle, int rows, int cols) {
    for (int r = rows; r < rows + needle.size(); ++r) {
        for (int c = cols; c < cols + needle[0].length(); ++c) {
            //cout << r << " " << c << "..... " << r - rows << " & " << c - cols << endl;
            if (haystack[r][c] != needle[r - rows][c - cols]) return false;
        }
    }

    return true;
}

bool gridExists(vector<string>& haystack, vector<string>& needle) {
    if (!haystack.size() && !needle.size() || !needle.size()) return true;
    if (needle.size() > haystack.size() || needle[0].size() > haystack[0].size()) return false;

    for (int r = 0; r < haystack.size() - needle.size() + 1; ++r) {
        for (int c = 0; c < haystack[0].size() - needle[0].length() + 1; ++c) {
            if (checkGridEquivalence(haystack, needle, r, c)) return true;
        }
    }

    return false;
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int R;
        int C;
        cin >> R >> C;
        vector<string> G(R);
        for(int G_i = 0;G_i < R;G_i++){
           cin >> G[G_i];
        }
        int r;
        int c;
        cin >> r >> c;
        vector<string> P(r);
        for(int P_i = 0;P_i < r;P_i++){
           cin >> P[P_i];
        }

        (gridExists(G, P)) ? cout << "YES" : cout << "NO";
        cout << endl;
    }
    return 0;
}
