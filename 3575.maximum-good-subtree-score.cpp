#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3575 lang=cpp
//
// [3575] Maximum Good Subtree Score
//

// @lc code=start
class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        static const int DIG = 10;
        static const int M = 1 << DIG;
        static const int MOD = 1'000'000'007;
        const long long NEG = (long long)-4e18;

        int n = (int)vals.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) children[par[i]].push_back(i);

        auto getMask = [&](long long x) -> int {
            int mask = 0;
            while (x > 0) {
                int d = (int)(x % 10);
                if (mask & (1 << d)) return -1; // repeated digit inside the number
                mask |= 1 << d;
                x /= 10;
            }
            return mask;
        };

        vector<int> valMask(n);
        for (int i = 0; i < n; i++) valMask[i] = getMask(vals[i]);

        // postorder traversal
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            order.push_back(u);
            for (int v : children[u]) st.push_back(v);
        }
        reverse(order.begin(), order.end());

        vector<array<long long, M>> dp(n);
        long long ans = 0;

        for (int u : order) {
            for (int i = 0; i < M; i++) dp[u][i] = NEG;
            dp[u][0] = 0;
            if (valMask[u] != -1) dp[u][valMask[u]] = max(dp[u][valMask[u]], (long long)vals[u]);

            // merge each child
            for (int v : children[u]) {
                vector<int> act1, act2;
                act1.reserve(M);
                act2.reserve(M);
                for (int m = 0; m < M; m++) {
                    if (dp[u][m] >= 0) act1.push_back(m);
                    if (dp[v][m] >= 0) act2.push_back(m);
                }

                array<long long, M> ndp;
                for (int i = 0; i < M; i++) ndp[i] = NEG;

                for (int m1 : act1) {
                    long long a = dp[u][m1];
                    for (int m2 : act2) {
                        if ((m1 & m2) != 0) continue;
                        int nm = m1 | m2;
                        ndp[nm] = max(ndp[nm], a + dp[v][m2]);
                    }
                }
                dp[u] = ndp;
            }

            long long best = 0;
            for (int m = 0; m < M; m++) best = max(best, dp[u][m]);
            ans += best;
            ans %= MOD;
        }

        return (int)(ans % MOD);
    }
};
// @lc code=end
