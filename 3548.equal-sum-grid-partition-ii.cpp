#include <bits/stdc++.h>
using namespace std;

/*
# @lc app=leetcode id=3548 lang=cpp
#
# [3548] Equal Sum Grid Partition II
#
*/

// @lc code=start
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = (int)grid.size();
        int n = (int)grid[0].size();

        const int MAXV = 100000;
        vector<long long> rowSum(m, 0), colSum(n, 0);
        long long totalSum = 0;

        unordered_map<int,int> totalCnt;
        totalCnt.reserve((size_t)m * (size_t)n * 2);
        totalCnt.max_load_factor(0.7f);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = grid[i][j];
                rowSum[i] += v;
                colSum[j] += v;
                totalSum += v;
                totalCnt[v]++;
            }
        }

        auto getCount = [&](const unordered_map<int,int>& mp, int key) -> int {
            auto it = mp.find(key);
            return it == mp.end() ? 0 : it->second;
        };

        unordered_map<int,int> prefCnt; // topCnt for horizontal, leftCnt for vertical
        prefCnt.reserve(totalCnt.size() * 2 + 1);
        prefCnt.max_load_factor(0.7f);

        // Checks if we can remove a cell of value diff from rectangle [r1..r2]x[c1..c2].
        // If usePref==true, the rectangle is the prefix tracked by prefCnt; otherwise it's the complement.
        auto canRemoveFromRect = [&](long long diff, int r1, int c1, int r2, int c2, bool usePref) -> bool {
            if (diff <= 0) return false;
            int h = r2 - r1 + 1;
            int w = c2 - c1 + 1;
            long long area = 1LL * h * w;

            // If discounting would remove the only cell, disallow.
            if (area <= 1) return false;

            // Line case: only endpoints are removable.
            if (h == 1 || w == 1) {
                int v1 = grid[r1][c1];
                int v2 = grid[r2][c2];
                return diff == v1 || diff == v2;
            }

            // General rectangle (h>=2 and w>=2): any cell is removable.
            if (diff > MAXV) return false; // cell values are <= 1e5
            int d = (int)diff;
            int tot = getCount(totalCnt, d);
            if (tot == 0) return false;
            int pre = getCount(prefCnt, d);
            int cntInRect = usePref ? pre : (tot - pre);
            return cntInRect > 0;
        };

        // 1) Horizontal cuts
        long long topSum = 0;
        for (int r = 0; r <= m - 2; r++) {
            topSum += rowSum[r];
            for (int j = 0; j < n; j++) prefCnt[grid[r][j]]++;

            long long bottomSum = totalSum - topSum;
            if (topSum == bottomSum) return true;

            if (topSum > bottomSum) {
                long long diff = topSum - bottomSum;
                // top rect: rows [0..r], cols [0..n-1]
                if (canRemoveFromRect(diff, 0, 0, r, n - 1, true)) return true;
            } else {
                long long diff = bottomSum - topSum;
                // bottom rect: rows [r+1..m-1], cols [0..n-1]
                if (canRemoveFromRect(diff, r + 1, 0, m - 1, n - 1, false)) return true;
            }
        }

        // 2) Vertical cuts
        prefCnt.clear();
        long long leftSum = 0;
        for (int c = 0; c <= n - 2; c++) {
            leftSum += colSum[c];
            for (int i = 0; i < m; i++) prefCnt[grid[i][c]]++;

            long long rightSum = totalSum - leftSum;
            if (leftSum == rightSum) return true;

            if (leftSum > rightSum) {
                long long diff = leftSum - rightSum;
                // left rect: rows [0..m-1], cols [0..c]
                if (canRemoveFromRect(diff, 0, 0, m - 1, c, true)) return true;
            } else {
                long long diff = rightSum - leftSum;
                // right rect: rows [0..m-1], cols [c+1..n-1]
                if (canRemoveFromRect(diff, 0, c + 1, m - 1, n - 1, false)) return true;
            }
        }

        return false;
    }
};
// @lc code=end
