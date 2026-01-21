#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> pre(n, 0);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            pre[v] |= (1 << u);
        }

        int N = 1 << n;
        vector<long long> dp(N, -1);
        dp[0] = 0;

        for (int mask = 0; mask < N; ++mask) {
            if (dp[mask] < 0) continue;
            int k = __builtin_popcount((unsigned)mask);
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                if ( (pre[v] & mask) != pre[v]) continue;
                int nmask = mask | (1 << v);
                dp[nmask] = max(dp[nmask], dp[mask] + 1LL * score[v] * (k + 1));
            }
        }

        return (int)dp[N - 1];
    }
};
# @lc code=end
