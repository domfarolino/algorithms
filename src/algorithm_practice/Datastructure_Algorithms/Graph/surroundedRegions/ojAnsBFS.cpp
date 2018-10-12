// Source: https://leetcode.com/problems/surrounded-regions/description/

class Solution {
public:
    struct pairHash {
    public:
      template <typename T, typename U>
      std::size_t operator()(const std::pair<T, U> &x) const
      {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
      }
    };

    void bfsGetEscaped(int r, int c, std::unordered_set<std::pair<int, int>, pairHash>& visited, const std::vector<std::vector<char>>& board) {
        if (board[r][c] == 'X') return;
        std::queue<std::pair<int, int>> q;
        q.push(std::make_pair(r, c));
        visited.insert(std::make_pair(r, c));

        std::pair<int, int> tmpPair;
        while (!q.empty()) {
            // Assert: q.front() is marked visited, but we've never seen/dealt with it before.
            r = q.front().first;
            c = q.front().second;

            // Top neighbor
            tmpPair = std::make_pair(r - 1, c);
            if (r - 1 >= 0 && board[r - 1][c] == 'O' && visited.find(tmpPair) == visited.end()) {
                visited.insert(tmpPair);
                q.push(tmpPair);
            }
            
            // Right neighbor
            tmpPair = std::make_pair(r, c + 1);
            if (c + 1 < board[0].size() && board[r][c + 1] == 'O' && visited.find(tmpPair) == visited.end()) {
                visited.insert(tmpPair);
                q.push(tmpPair);
            }
            
            // Bottom neighbor
            tmpPair = std::make_pair(r + 1, c);
            if (r + 1 < board.size() && board[r + 1][c] == 'O' && visited.find(tmpPair) == visited.end()) {
                visited.insert(tmpPair);
                q.push(tmpPair);
            }
            
            // Left neighbor
            tmpPair = std::make_pair(r, c - 1);
            if (c - 1 >= 0 && board[r][c - 1] == 'O' && visited.find(tmpPair) == visited.end()) {
                visited.insert(tmpPair);
                q.push(tmpPair);
            }

            q.pop();
        }
    }

    void solve(vector<vector<char>>& board) {
        if (!board.size()) return;
        std::unordered_set<std::pair<int, int>, pairHash> visited;

        // Visit all "O"s touching the outside rows
        for (int c = 0; c < board[0].size(); ++c) {
            bfsGetEscaped(0, c, visited, board);
            bfsGetEscaped(board.size() - 1, c, visited, board);
        }

        // Visit all "O"s touching the outside columns
        for (int r = 0; r < board.size(); ++r) {
            bfsGetEscaped(r, 0, visited, board);
            bfsGetEscaped(r, board[0].size() - 1, visited, board);
        }
        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board[r].size(); ++c) {
                if (visited.find(std::make_pair(r, c)) == visited.end())
                    board[r][c] = 'X';
            }
        }
    }
};
