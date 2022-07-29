#include <iostream>
#include <utility>
#include <vector>

// Source: ACM ICPC 2018 Practice

void printWinnerAndLeadTimes(const std::vector<std::tuple<char, int, int, int>>& scores) {
  // scores = <team, point, min, sec>
  std::tuple<int, int, int> H, A;
  int lastHLeadMin = 0, lastHLeadSec = 0,
      lastALeadMin = 0, lastALeadSec = 0;
  char L = 'N';

  for (int i = 0; i < scores.size(); ++i) {
    if (std::get<0>(scores[i]) == 'H') {
      // Home team scored.
      std::get<0>(H) += std::get<1>(scores[i]);
    } else {
      // Away team scored.
      std::get<0>(A) += std::get<1>(scores[i]);
    }

    // A team scored.
    // 1.) The team that was leading scored, so we do nothing with the time.
    // 2.) The team that was losing scored, so we must update the previous
    //     leader's max leading time with the difference from "now" to the
    //     last time they scored.
    // 3.) A team took the lead when there was previously no leader. Nobody's
    //     time gets updated here, but we need to update `L` anyways.
    // With (2), we either change the leader `L` to the new team, or 'N' if
    // the new scorer didn't score enough to take the lead. Either way.
    if (L == 'H' && std::get<0>(H) > std::get<0>(A) ||
        L == 'A' && std::get<0>(A) > std::get<0>(H)) {
      continue;
    }

    // Assert: Someone scored and either:
    //   1.) Stole the lead
    //   2.) Evened the game
    if (L == 'N') {
      // Update new winning team's last-took-lead-time
      // L = winning team
      if (std::get<0>(H) > std::get<0>(A)) {
        L = 'H';
        lastHLeadMin = std::get<2>(scores[i]);
        lastHLeadSec = std::get<3>(scores[i]);
      } else {
        L = 'A';
        lastALeadMin = std::get<2>(scores[i]);
        lastALeadSec = std::get<3>(scores[i]);
      }
    } else if {
      // 1.) There is a new winner
      //   - Update previous winning team's max lead time
      //   - L = winning team
      //   - Set new winning team's last-took-lead-time
      if (std::get<0>(H) != std::get<0>(A)) {
        // ...
      }
      // 2.) Evened out the game
      //   - Update previous winning team's max lead time
      //   - L = 'N'
      else {
        L = 'N';
      }
    }

    // The leader `L` is about to change, so we have to update this leader's
    // max leading time.
  }

  // Consider time 32:00 here.

  if (std::get<0>(H) > std::get<0>(A))
    std::cout << "H ";
  else
    std::cout << "A ";

  std::cout << std::get<1>(H) << ":" << std::get<2>(H) << " ";
  std::cout << std::get<1>(A) << ":" << std::get<2>(A) << std::endl;
}

int main() {
  int n;
  std::vector<std::tuple<char, int, int, int>> scores;
  std::cin >> n;

  char team, tmp;
  int point, mins, secs;
  for (int i = 0; i < n; ++i) {
    std::cin >> team >> point >> mins >> tmp >> secs;
    scores.push_back(std::tie(team, point, mins, secs));
  }

  printWinnerAndLeadTimes(scores);
  return 0;
}
