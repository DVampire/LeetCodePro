#
# @lc app=leetcode id=3548 lang=cpp
#
# [3548] Equal Sum Grid Partition II
#

# @lc code=start
#include <vector>
#include <numeric>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long totalSum = 0;
        for (const auto& row : grid) {
            for (int val : row) totalSum += val;
        }

        // Check Horizontal Cuts
        if (m > 1) {
            unordered_map<int, int> count1, count2;
            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < n; ++c) count2[grid[r][c]]++;
            }
            long long s1 = 0;
            for (int i = 0; i < m - 1; ++i) {
                for (int c = 0; c < n; ++c) {
                    int val = grid[i][c];
                    count1[val]++;
                    if (--count2[val] == 0) count2.erase(val);
                    s1 += val;
                }
                long long s2 = totalSum - s1;
                if (s1 == s2) return true;
                
                if (s1 > s2) {
                    long long x = s1 - s2;
                    if (n > 1 && i + 1 > 1) { if (count1.count(x)) return true; }
                    else if (n > 1 && i + 1 == 1) { if (x == grid[0][0] || x == grid[0][n - 1]) return true; }
                    else if (n == 1 && i + 1 > 1) { if (x == grid[0][0] || x == grid[i][0]) return true; }
                    else if (n == 1 && i + 1 == 1) { if (x == grid[0][0]) return true; }
                }
                
                if (s2 > s1) {
                    long long y = s2 - s1;
                    int r2 = m - 1 - i;
                    if (n > 1 && r2 > 1) { if (count2.count(y)) return true; }
                    else if (n > 1 && r2 == 1) { if (y == grid[i + 1][0] || y == grid[i + 1][n - 1]) return true; }
                    else if (n == 1 && r2 > 1) { if (y == grid[i + 1][0] || y == grid[m - 1][0]) return true; }
                    else if (n == 1 && r2 == 1) { if (y == grid[i + 1][0]) return true; }
                }
            }
        }

        // Check Vertical Cuts
        if (n > 1) {
            unordered_map<int, int> count1, count2;
            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < n; ++c) count2[grid[r][c]]++;
            }
            long long s1 = 0;
            for (int j = 0; j < n - 1; ++j) {
                for (int r = 0; r < m; ++r) {
                    int val = grid[r][j];
                    count1[val]++;
                    if (--count2[val] == 0) count2.erase(val);
                    s1 += val;
                }
                long long s2 = totalSum - s1;
                if (s1 == s2) return true;

                if (s1 > s2) {
                    long long x = s1 - s2;
                    if (m > 1 && j + 1 > 1) { if (count1.count(x)) return true; }
                    else if (m > 1 && j + 1 == 1) { if (x == grid[0][0] || x == grid[m - 1][0]) return true; }
                    else if (m == 1 && j + 1 > 1) { if (x == grid[0][0] || x == grid[0][j]) return true; }
                    else if (m == 1 && j + 1 == 1) { if (x == grid[0][0]) return true; }
                }

                if (s2 > s1) {
                    long long y = s2 - s1;
                    int c2 = n - 1 - j;
                    if (m > 1 && c2 > 1) { if (count2.count(y)) return true; }
                    else if (m > 1 && c2 == 1) { if (y == grid[0][j + 1] || y == grid[m - 1][j + 1]) return true; }
                    else if (m == 1 && c2 > 1) { if (y == grid[0][j + 1] || y == grid[0][n - 1]) return true; }
                    else if (m == 1 && c2 == 1) { if (y == grid[0][j + 1]) return true; }
                }
            }
        }

        return false;
    }
};
# @lc code=end