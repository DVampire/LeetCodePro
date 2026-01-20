#
# @lc app=leetcode id=3459 lang=cpp
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int memo[500][500][4][2][2];

class Solution {
    int dr[4] = {1, 1, -1, -1};
    int dc[4] = {1, -1, -1, 1};
    int n, m;

    int solve(int r, int c, int d, int turned, int val_idx, const vector<vector<int>>& grid) {
        if (memo[r][c][d][turned][val_idx] != -1) return memo[r][c][d][turned][val_idx];

        int current_val = (val_idx == 0) ? 0 : 2;
        int target_val = 2 - current_val;
        int target_idx = 1 - val_idx;
        int res = 1;

        // Option 1: Continue in current direction
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == target_val) {
            res = max(res, 1 + solve(nr, nc, d, turned, target_idx, grid));
        }

        // Option 2: Turn clockwise (only if not already turned)
        if (turned == 0) {
            int nd = (d + 1) % 4;
            int nr2 = r + dr[nd], nc2 = c + dc[nd];
            if (nr2 >= 0 && nr2 < n && nc2 >= 0 && nc2 < m && grid[nr2][nc2] == target_val) {
                res = max(res, 1 + solve(nr2, nc2, nd, 1, target_idx, grid));
            }
        }

        return memo[r][c][d][turned][val_idx] = res;
    }

public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        memset(memo, -1, sizeof(memo));

        int max_len = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    max_len = max(max_len, 1);
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dr[d], nj = j + dc[d];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == 2) {
                            max_len = max(max_len, 1 + solve(ni, nj, d, 0, 1, grid));
                        }
                    }
                }
            }
        }

        return max_len;
    }
};
# @lc code=end