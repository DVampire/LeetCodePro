#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countEffective(vector<int>& nums) {
        const long long MOD = 1000000007LL;
        int n = nums.size();
        int total_or = 0;
        for (int x : nums) total_or |= x;
        vector<int> bits;
        for (int b = 0; b < 30; ++b) {
            if (total_or & (1 << b)) bits.push_back(b);
        }
        int m = bits.size();
        int M = 1 << m;
        vector<long long> freq(M, 0);
        for (int x : nums) {
            int s = 0;
            for (int j = 0; j < m; ++j) {
                if (x & (1 << bits[j])) s |= (1 << j);
            }
            ++freq[s];
        }
        vector<long long> dp = freq;
        for (int j = 0; j < m; ++j) {
            for (int mask = 0; mask < M; ++mask) {
                if (mask & (1 << j)) {
                    dp[mask] += dp[mask ^ (1 << j)];
                }
            }
        }
        int full = M - 1;
        vector<long long> p2(n + 1);
        p2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p2[i] = p2[i - 1] * 2 % MOD;
        }
        long long ans = 0;
        for (int k = 1; k < M; ++k) {
            int comp = full ^ k;
            long long g = dp[comp];
            long long uk = (long long)n - g;
            long long ways = p2[n - uk];
            int pop = __builtin_popcount(k);
            if (pop & 1) {
                ans = (ans + ways) % MOD;
            } else {
                ans = (ans + MOD - ways) % MOD;
            }
        }
        return ans;
    }
};
# @lc code=end