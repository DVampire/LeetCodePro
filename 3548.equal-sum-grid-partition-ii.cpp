#
# @lc app=leetcode id=3548 lang=cpp
#
# [3548] Equal Sum Grid Partition II
#

# @lc code=start
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long totalSum = 0;

        // Frequency arrays for values. Max value is 10^5.
        // Using vectors is safer and fast enough.
        vector<int> bottomCount(100005, 0);
        vector<int> topCount(100005, 0);

        for(const auto& row : grid) {
            for(int val : row) {
                totalSum += val;
                bottomCount[val]++;
            }
        }

        long long topSum = 0;
        long long bottomSum = totalSum;

        // Try Horizontal Cuts
        // Cut is after row i. i ranges from 0 to m-2.
        for (int i = 0; i < m; ++i) {
            // Move row i from bottom to top
            for (int val : grid[i]) {
                bottomCount[val]--;
                topCount[val]++;
                topSum += val;
                bottomSum -= val;
            }

            // If this is the last row, we can't cut after it
            if (i == m - 1) continue;

            if (topSum == bottomSum) return true;

            long long diff = abs(topSum - bottomSum);
            if (diff > 100000) continue; // Cannot remove such a large value

            if (topSum > bottomSum) {
                // Need to remove 'diff' from top
                // Top section is rows 0 to i. Height is i+1. Width is n.
                // It is connected unless width == 1 AND height > 1 AND we remove an internal node.
                if (n > 1 || (i + 1) == 1) {
                    if (topCount[diff] > 0) return true;
                } else {
                    // n == 1 and height > 1. Can only remove endpoints of the top section.
                    // Endpoints are (0,0) and (i,0).
                    if (grid[0][0] == diff || grid[i][0] == diff) return true;
                }
            } else {
                // Need to remove 'diff' from bottom
                // Bottom section is rows i+1 to m-1. Height is m - 1 - i. Width is n.
                if (n > 1 || (m - 1 - i) == 1) {
                    if (bottomCount[diff] > 0) return true;
                } else {
                    // n == 1 and height > 1.
                    // Endpoints are (i+1, 0) and (m-1, 0).
                    if (grid[i+1][0] == diff || grid[m-1][0] == diff) return true;
                }
            }
        }

        // Try Vertical Cuts
        // Reset counts
        vector<int> rightCount(100005, 0);
        vector<int> leftCount(100005, 0);
        
        // Re-populate rightCount with all values
        // Note: We could have copied from bottomCount initially if we hadn't modified it,
        // but re-scanning is O(MN) which is fine.
        for(const auto& row : grid) {
            for(int val : row) {
                rightCount[val]++;
            }
        }

        long long leftSum = 0;
        long long rightSum = totalSum;

        // Cut is after column j. j ranges from 0 to n-2.
        for (int j = 0; j < n; ++j) {
            // Move col j from right to left
            for (int r = 0; r < m; ++r) {
                int val = grid[r][j];
                rightCount[val]--;
                leftCount[val]++;
                leftSum += val;
                rightSum -= val;
            }

            if (j == n - 1) continue;

            if (leftSum == rightSum) return true;

            long long diff = abs(leftSum - rightSum);
            if (diff > 100000) continue;

            if (leftSum > rightSum) {
                // Remove from left. Left is cols 0..j. Width j+1, Height m.
                if (m > 1 || (j + 1) == 1) {
                    if (leftCount[diff] > 0) return true;
                } else {
                    // m == 1, width > 1. Line graph. Endpoints (0,0) and (0,j).
                    if (grid[0][0] == diff || grid[0][j] == diff) return true;
                }
            } else {
                // Remove from right. Right is cols j+1..n-1. Width n-1-j, Height m.
                if (m > 1 || (n - 1 - j) == 1) {
                    if (rightCount[diff] > 0) return true;
                } else {
                    // m == 1, width > 1. Endpoints (0, j+1) and (0, n-1).
                    if (grid[0][j+1] == diff || grid[0][n-1] == diff) return true;
                }
            }
        }

        return false;
    }
};
# @lc code=end