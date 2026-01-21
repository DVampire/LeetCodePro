#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#
# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        // Build bitmask for prerequisites
        vector<int> prereq_mask(n, 0);
        for (auto& e : edges) {
            prereq_mask[e[1]] |= (1 << e[0]);
        }
        
        // dp[mask] = maximum profit when nodes in mask are processed
        vector<long long> dp(1 << n, -1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == -1) continue;
            
            int position = __builtin_popcount(mask) + 1;
            
            // Try to add each unprocessed node
            for (int node = 0; node < n; node++) {
                if (mask & (1 << node)) continue;
                
                // Check if all prerequisites are satisfied
                if ((prereq_mask[node] & mask) == prereq_mask[node]) {
                    int new_mask = mask | (1 << node);
                    long long profit = dp[mask] + (long long)score[node] * position;
                    dp[new_mask] = max(dp[new_mask], profit);
                }
            }
        }
        
        return (int)dp[(1 << n) - 1];
    }
};
# @lc code=end