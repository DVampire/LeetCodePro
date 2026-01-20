#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        int n = coins.size();
        sort(coins.begin(), coins.end());

        long long max_coins = 0;

        // Case 1: Window starts at the beginning of a segment l_i
        // Window: [coins[i][0], coins[i][0] + k - 1]
        long long current_sum = 0;
        for (int i = 0, j = 0; i < n; ++i) {
            // Add segments that are fully inside the window [l_i, l_i + k - 1]
            while (j < n && (long long)coins[j][1] <= (long long)coins[i][0] + k - 1) {
                current_sum += (long long)(coins[j][1] - coins[j][0] + 1) * coins[j][2];
                j++;
            }
            
            long long total = current_sum;
            // Add partial overlap with the segment j (the first segment ending after the window)
            if (j < n && (long long)coins[j][0] <= (long long)coins[i][0] + k - 1) {
                total += (long long)((long long)coins[i][0] + k - 1 - coins[j][0] + 1) * coins[j][2];
            }
            max_coins = max(max_coins, total);

            // Slide window: remove current segment i from the sum if it was added
            if (j > i) {
                current_sum -= (long long)(coins[i][1] - coins[i][0] + 1) * coins[i][2];
            } else {
                // If current segment i was never added (it's longer than k), move j forward
                j = i + 1;
                current_sum = 0;
            }
        }

        // Case 2: Window ends at the end of a segment r_i
        // Window: [coins[i][1] - k + 1, coins[i][1]]
        current_sum = 0;
        for (int i = 0, j = 0; i < n; ++i) {
            current_sum += (long long)(coins[i][1] - coins[i][0] + 1) * coins[i][2];
            // Remove segments that start before the window [r_i - k + 1, r_i]
            while (j <= i && (long long)coins[j][0] < (long long)coins[i][1] - k + 1) {
                current_sum -= (long long)(coins[j][1] - coins[j][0] + 1) * coins[j][2];
                j++;
            }

            long long total = current_sum;
            // Add partial overlap with the segment j-1 (the last segment starting before the window)
            if (j > 0 && (long long)coins[j - 1][1] >= (long long)coins[i][1] - k + 1) {
                total += (long long)(coins[j - 1][1] - ((long long)coins[i][1] - k + 1) + 1) * coins[j - 1][2];
            }
            max_coins = max(max_coins, total);
        }

        return max_coins;
    }
};
# @lc code=end