#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        // pre[i] stores the bitmask of all direct predecessors of node i
        vector<int> pre(n, 0);
        for (const auto& edge : edges) {
            pre[edge[1]] |= (1 << edge[0]);
        }

        // dp[mask] stores the maximum profit using the nodes represented by the bitmask
        // Since n <= 22 and scores <= 10^5, the max profit is roughly 2.5 * 10^7, which fits in int.
        // However, we use long long for safety during intermediate calculations.
        vector<long long> dp(1 << n, -1);
        dp[0] = 0;

        for (int mask = 0; mask < (1 << n); ++mask) {
            if (dp[mask] == -1) continue;

            // k is the number of nodes already placed, so the next node will be at position k + 1
            int k = __builtin_popcount(mask);
            int next_pos = k + 1;

            // Try adding each node i that is not in the current mask
            int not_mask = ((1 << n) - 1) ^ mask;
            while (not_mask > 0) {
                // Extract the index of the lowest set bit
                int i = __builtin_ctz(not_mask);
                
                // Check if all predecessors of node i are already in the mask
                if ((pre[i] & mask) == pre[i]) {
                    int next_mask = mask | (1 << i);
                    long long current_profit = dp[mask] + (long long)score[i] * next_pos;
                    if (current_profit > dp[next_mask]) {
                        dp[next_mask] = current_profit;
                    }
                }
                
                // Remove the lowest set bit to continue the loop
                not_mask &= (not_mask - 1);
            }
        }

        return dp[(1 << n) - 1];
    }
};
# @lc code=end