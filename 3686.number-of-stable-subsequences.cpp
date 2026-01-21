#include <vector>
using namespace std;

/*
 * @lc app=leetcode id=3686 lang=cpp
 *
 * [3686] Number of Stable Subsequences
 */

// @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        static const int MOD = 1'000'000'007;
        long long dp[2][3] = {}; // dp[p][1], dp[p][2]

        for (int x : nums) {
            int q = x & 1;
            long long add1 = 1; // start from empty
            add1 = (add1 + dp[1 - q][1] + dp[1 - q][2]) % MOD;
            long long add2 = dp[q][1] % MOD; // must use old dp[q][1]

            dp[q][2] = (dp[q][2] + add2) % MOD;
            dp[q][1] = (dp[q][1] + add1) % MOD;
        }

        long long ans = (dp[0][1] + dp[0][2] + dp[1][1] + dp[1][2]) % MOD;
        return (int)ans;
    }
};
// @lc code=end
