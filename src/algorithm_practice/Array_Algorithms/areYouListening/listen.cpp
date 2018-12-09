#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

// Source: ACM ICPC 2018 Practice

int computeDistance(int homeX, int homeY, int otherX, int otherY, int rad) {
  int retDist = sqrt(pow((homeX - otherX), 2) + pow((homeY - otherY), 2)) - rad;
  return retDist;
}

int main() {
  int startX, startY, numDevices;
  std::cin >> startX >> startY >> numDevices;

  std::vector<int> distances;
  int devX, devY, devR;
  int dist;
  for (int i = 0; i < numDevices; ++i) {
    std::cin >> devX >> devY >> devR;
    dist = computeDistance(startX, startY, devX, devY, devR);
    if (dist < 0) dist = 0;
    distances.push_back(dist);
  }

  std::sort(distances.begin(), distances.end());
  std::cout << distances[2] << std::endl;
  return 0;
}
