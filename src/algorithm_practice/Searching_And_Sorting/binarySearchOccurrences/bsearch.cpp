#include <iostream>
#include <vector>

using namespace std;

// Source: http://www.geeksforgeeks.org/count-number-of-occurrences-in-a-sorted-array/
// Souce: UVa (see AOAPC>V0>489)

/**
 * Binary Search
 * - First Occurrence
 * - Last Occurrrence
 * - Total number of occurrences ( = last - first + 1)
 */

int firstOccurrence(const vector<int>& haystack, int low, int high, int needle) {
  // Set this now so if the while loop is never
  // entered we don't segfault on return conditional
  int mid = low + (high - low)/2;
    
  while (low <= high) {
    mid = low + (high - low)/2;
    
    if (haystack[mid] < needle) {
      low = mid + 1;
    } else if (haystack[mid] > needle) {
      high = mid - 1;
    } else {
      int farthestLeft = firstOccurrence(haystack, low, mid-1, needle);
      if (farthestLeft != -1) mid = farthestLeft;
      break;
    }
  }

  return (haystack[mid] == needle) ? mid : -1;
}

int lastOccurrence(const vector<int>& haystack, int low, int high, int needle) {
  // Set this now so if the while loop is never
  // entered we don't segfault on return conditional
  int mid = low + (high - low)/2;
  
  while (low <= high) {
    mid = low + (high - low)/2;
    
    if (haystack[mid] < needle) {
      low = mid + 1;
    } else if (haystack[mid] > needle) {
      high = mid - 1;
    } else {
      int farthestRight = lastOccurrence(haystack, mid+1, high, needle);
      if (farthestRight != -1) mid = farthestRight;
      break;
    }
  }

  return (haystack[mid] == needle) ? mid : -1;
}

int numOccurrences(const vector<int>& haystack, int needle) {
  int first = firstOccurrence(haystack, 0, haystack.size()-1, needle);
  if (first == -1) return first;
  
  int last = lastOccurrence(haystack, 0, haystack.size()-1, needle);
  
  return last - first + 1;
}

int main() {
  int total, length, needle, tmp;
  vector<int> haystack;

  cin >> total;

  for (int i = 0; i < total; ++i) {
    cin >> length >> needle;
    haystack.reserve(length);

    for (int j = 0; j < length; ++j) {
      cin >> tmp;
      haystack.push_back(tmp);
    }

    cout << numOccurrences(haystack, needle) << endl;

    haystack.clear();
  }

  return 0;
}