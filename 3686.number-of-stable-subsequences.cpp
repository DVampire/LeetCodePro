#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        
        // dp[parity][count]
        // parity: 0 (even), 1 (odd)
        // count: 1 or 2 (number of consecutive elements with that parity at the end)
        vector<vector<long long>> dp(2, vector<long long>(3, 0));
        
        for (int num : nums) {
            int parity = num % 2;
            int other = 1 - parity;
            
            vector<vector<long long>> new_dp = dp;
            
            // Start a new subsequence with this element
            new_dp[parity][1] = (new_dp[parity][1] + 1) % MOD;
            
            // Extend subsequences with same parity (only from count=1 to count=2)
            new_dp[parity][2] = (new_dp[parity][2] + dp[parity][1]) % MOD;
            
            // Extend subsequences with different parity (reset count to 1)
            new_dp[parity][1] = (new_dp[parity][1] + dp[other][1]) % MOD;
            new_dp[parity][1] = (new_dp[parity][1] + dp[other][2]) % MOD;
            
            dp = new_dp;
        }
        
        // Sum all stable subsequences
        long long result = (dp[0][1] + dp[0][2] + dp[1][1] + dp[1][2]) % MOD;
        return result;
    }
};
# @lc code=end