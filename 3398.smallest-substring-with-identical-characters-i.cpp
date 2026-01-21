#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3398 lang=cpp
//
// [3398] Smallest Substring With Identical Characters I
//

// @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = (int)s.size();

        auto feasible = [&](int L) -> bool {
            const int INF = 1e9;
            vector<vector<int>> dp(2, vector<int>(L + 1, INF));

            // i = 0 initialization
            for (int c = 0; c <= 1; c++) {
                int cost = ((s[0] - '0') != c);
                dp[c][1] = min(dp[c][1], cost);
            }

            for (int i = 1; i < n; i++) {
                vector<vector<int>> ndp(2, vector<int>(L + 1, INF));
                for (int prev = 0; prev <= 1; prev++) {
                    for (int len = 1; len <= L; len++) {
                        int cur = dp[prev][len];
                        if (cur >= INF) continue;
                        for (int c = 0; c <= 1; c++) {
                            int nlen = (c == prev) ? (len + 1) : 1;
                            if (nlen > L) continue;
                            int add = ((s[i] - '0') != c);
                            ndp[c][nlen] = min(ndp[c][nlen], cur + add);
                        }
                    }
                }
                dp.swap(ndp);
            }

            int best = INT_MAX;
            for (int c = 0; c <= 1; c++)
                for (int len = 1; len <= L; len++)
                    best = min(best, dp[c][len]);
            return best <= numOps;
        };

        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
// @lc code=end
