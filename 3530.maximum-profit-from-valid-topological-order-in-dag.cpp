#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        // Precompute parents bitmasks
        // parents[i] contains a bitmask where the j-th bit is set if there is an edge j -> i
        vector<int> parents(n, 0);
        for (const auto& edge : edges) {
            parents[edge[1]] |= (1 << edge[0]);
        }

        // dp[mask] stores the max profit for the set of nodes in mask
        // utilizing positions 1 to k, where k is the number of set bits in mask.
        // Initialize with -1 to represent unreachable states.
        vector<int> dp(1 << n, -1);
        dp[0] = 0;

        // Iterate through all masks
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (dp[mask] == -1) continue;

            // The position for the next node will be (number of nodes currently in mask) + 1
            int next_pos = __builtin_popcount(mask) + 1;

            // Try to add any node u that is not yet in mask
            for (int u = 0; u < n; ++u) {
                // If u is not in mask
                if (!((mask >> u) & 1)) {
                    // Check if all dependencies of u are already in mask
                    // parents[u] must be a subset of mask
                    if ((parents[u] & mask) == parents[u]) {
                        int next_mask = mask | (1 << u);
                        int new_profit = dp[mask] + score[u] * next_pos;
                        if (new_profit > dp[next_mask]) {
                            dp[next_mask] = new_profit;
                        }
                    }
                }
            }
        }

        return dp[(1 << n) - 1];
    }
};
# @lc code=end