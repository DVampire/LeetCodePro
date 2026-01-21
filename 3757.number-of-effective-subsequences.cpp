#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#
# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        
        // Calculate total OR
        int total_or = 0;
        for (int num : nums) {
            total_or |= num;
        }
        
        // dp[mask] = number of ways to have remaining OR = mask
        unordered_map<int, long long> dp;
        dp[0] = 1;
        
        for (int num : nums) {
            unordered_map<int, long long> new_dp;
            for (const auto& [mask, count] : dp) {
                // Remove this element from remaining (add to subsequence)
                new_dp[mask] = (new_dp[mask] + count) % MOD;
                
                // Keep this element in remaining (don't add to subsequence)
                int new_mask = mask | num;
                new_dp[new_mask] = (new_dp[new_mask] + count) % MOD;
            }
            dp = std::move(new_dp);
        }
        
        // Count effective subsequences (where remaining OR < total OR)
        long long result = 0;
        for (const auto& [mask, count] : dp) {
            if (mask < total_or) {
                result = (result + count) % MOD;
            }
        }
        
        return result;
    }
};
# @lc code=end