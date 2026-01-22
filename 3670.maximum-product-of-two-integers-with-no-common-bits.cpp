#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#
# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        const int MAX_BITS = 20;
        const int SIZE = 1 << MAX_BITS;
        
        vector<int> dp(SIZE, 0);
        
        // Initialize dp with exact matches
        for (int x : nums) {
            dp[x] = max(dp[x], x);
        }
        
        // SOS DP: compute max over all subsets
        for (int bit = 0; bit < MAX_BITS; bit++) {
            for (int mask = 0; mask < SIZE; mask++) {
                if (mask & (1 << bit)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
                }
            }
        }
        
        long long ans = 0;
        for (int x : nums) {
            // Complement within 20 bits
            int complement = (SIZE - 1) ^ x;
            ans = max(ans, (long long)x * dp[complement]);
        }
        
        return ans;
    }
};
# @lc code=end