#
# @lc app=leetcode id=3538 lang=cpp
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<long long> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + time[i - 1];
        }
        const long long INF = LLONG_MAX / 2;
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(101, INF)));
        int t0 = time[0];
        dp[0][0][t0] = 0;
        for (int q = 0; q < n; ++q) {
            for (int u = 0; u <= k; ++u) {
                for (int s = 0; s <= 100; ++s) {
                    if (dp[q][u][s] == INF) continue;
                    for (int p = q + 1; p < n; ++p) {
                        int num_signs = p - q;
                        int mrg = num_signs - 1;
                        int nu = u + mrg;
                        if (nu > k) continue;
                        long long ns = prefix[p + 1] - prefix[q + 1];
                        if (ns > 100 || ns <= 0) continue;
                        long long dist = (long long)position[p] - position[q];
                        long long addc = dist * s;
                        long long nc = dp[q][u][s] + addc;
                        if (nc < dp[p][nu][(int)ns]) {
                            dp[p][nu][(int)ns] = nc;
                        }
                    }
                }
            }
        }
        long long ans = INF;
        for (int s = 0; s <= 100; ++s) {
            ans = min(ans, dp[n - 1][k][s]);
        }
        return (int)ans;
    }
};
# @lc code=end
