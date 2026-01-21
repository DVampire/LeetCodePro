#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3670 lang=cpp
 *
 * [3670] Maximum Product of Two Integers With No Common Bits
 */

// @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        static constexpr int B = 20;                 // since 1e6 < 2^20
        static constexpr int FULL = (1 << B) - 1;
        const int SZ = 1 << B;

        vector<int> best(SZ, 0);
        for (int x : nums) best[x] = max(best[x], x);

        // dp[mask] = maximum value present among all submasks of mask
        vector<int> dp = best;
        for (int i = 0; i < B; ++i) {
            for (int mask = 0; mask < SZ; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
                }
            }
        }

        long long ans = 0;
        for (int a : nums) {
            int b = dp[FULL ^ a];
            ans = max(ans, 1LL * a * b);
        }
        return ans;
    }
};
// @lc code=end
