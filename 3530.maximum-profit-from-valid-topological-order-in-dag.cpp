#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> pred(n, 0);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            pred[v] |= (1 << u);
        }
        int N = 1 << n;
        vector<long long> dp(N, -(1LL << 60));
        dp[0] = 0;
        for (int S = 0; S < N; ++S) {
            if (dp[S] == -(1LL << 60)) continue;
            int pos = __builtin_popcount(S) + 1;
            for (int v = 0; v < n; ++v) {
                if ((S & (1 << v)) == 0) {
                    if ((pred[v] & S) == pred[v]) {
                        int nS = S | (1 << v);
                        long long nprof = dp[S] + 1LL * score[v] * pos;
                        if (nprof > dp[nS]) {
                            dp[nS] = nprof;
                        }
                    }
                }
            }
        }
        return dp[N - 1];
    }
};
# @lc code=end