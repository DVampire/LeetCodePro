#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        const int BITS = 20;
        const int MAXM = 1 << BITS;
        vector<long long> maxval(MAXM, 0);
        for (int num : nums) {
            int mask = num;
            maxval[mask] = max(maxval[mask], (long long)num);
        }
        auto dp = maxval;
        for (int b = 0; b < BITS; ++b) {
            for (int s = 0; s < MAXM; ++s) {
                if (s & (1 << b)) {
                    dp[s] = max(dp[s], dp[s ^ (1 << b)]);
                }
            }
        }
        int ALL = MAXM - 1;
        long long ans = 0;
        for (int m = 0; m < MAXM; ++m) {
            if (maxval[m] > 0) {
                int comp = ALL ^ m;
                long long prod = maxval[m] * dp[comp];
                ans = max(ans, prod);
            }
        }
        return ans;
    }
};
# @lc code=end