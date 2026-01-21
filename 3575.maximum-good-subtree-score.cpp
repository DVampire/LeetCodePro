#
# @lc app=leetcode id=3575 lang=cpp
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; ++i) {
            children[par[i]].push_back(i);
        }
        vector<int> masks(n, 0);
        auto get_mask = [](int x) -> int {
            int m = 0;
            string s = to_string(x);
            for (char c : s) {
                int d = c - '0';
                int bit = 1 << d;
                if (m & bit) return 0;
                m |= bit;
            }
            return m;
        };
        for (int i = 0; i < n; ++i) {
            masks[i] = get_mask(vals[i]);
        }
        const long long INF = 1LL << 60;
        const int MS = 1 << 10;
        vector<vector<long long>> dp(n, vector<long long>(MS, -INF));
        const int MOD = 1000000007;
        long long answer = 0;
        function<void(int)> dfs = [&](int u) {
            vector<long long> curr(MS, -INF);
            curr[0] = 0;
            for (int v : children[u]) {
                dfs(v);
                vector<long long> nxt(MS, -INF);
                vector<int> act_curr, act_v;
                for (int j = 0; j < MS; ++j) {
                    if (curr[j] != -INF) act_curr.push_back(j);
                    if (dp[v][j] != -INF) act_v.push_back(j);
                }
                for (int pm : act_curr) {
                    for (int cm : act_v) {
                        if ((pm & cm) == 0) {
                            int nm = pm | cm;
                            nxt[nm] = max(nxt[nm], curr[pm] + dp[v][cm]);
                        }
                    }
                }
                curr = std::move(nxt);
            }
            vector<long long> this_dp(MS, -INF);
            int mu = masks[u];
            long long vu = vals[u];
            bool can = (mu != 0);
            vector<int> act_c;
            for (int j = 0; j < MS; ++j) {
                if (curr[j] != -INF) act_c.push_back(j);
            }
            for (int m : act_c) {
                this_dp[m] = max(this_dp[m], curr[m]);
                if (can && (m & mu) == 0) {
                    int nm = m | mu;
                    this_dp[nm] = max(this_dp[nm], curr[m] + vu);
                }
            }
            dp[u] = std::move(this_dp);
            long long mx = 0;
            for (int j = 0; j < MS; ++j) {
                mx = max(mx, dp[u][j]);
            }
            answer = (answer + mx) % MOD;
        };
        dfs(0);
        return answer;
    }
};
# @lc code=end
