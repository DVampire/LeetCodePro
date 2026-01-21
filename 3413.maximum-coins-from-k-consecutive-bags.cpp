#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3413 lang=cpp
 *
 * [3413] Maximum Coins From K Consecutive Bags
 */

// @lc code=start
class Solution {
    using ll = long long;

    static ll solveLeftAnchored(vector<array<ll,3>> segs, ll k) {
        // seg: [l, r, c], inclusive, non-overlapping
        sort(segs.begin(), segs.end(), [](const auto& a, const auto& b){
            return a[0] < b[0];
        });

        int n = (int)segs.size();
        vector<ll> l(n), r(n), c(n);
        for (int i = 0; i < n; i++) {
            l[i] = segs[i][0];
            r[i] = segs[i][1];
            c[i] = segs[i][2];
        }

        vector<ll> pre(n + 1, 0); // pre[i] = total coins in segments [0..i-1]
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + (r[i] - l[i] + 1) * c[i];
        }

        ll best = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < i) j = i;
            ll start = l[i];
            ll end = start + k - 1;

            while (j < n && r[j] <= end) j++;

            ll sum = pre[j] - pre[i];
            if (j < n && l[j] <= end) {
                sum += (end - l[j] + 1) * c[j];
            }
            best = max(best, sum);
        }
        return best;
    }

public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        ll K = (ll)k;
        int n = (int)coins.size();

        vector<array<ll,3>> segs;
        segs.reserve(n);
        for (auto &v : coins) {
            ll l = v[0], r = v[1], c = v[2];
            segs.push_back({l, r, c});
        }

        ll ans = solveLeftAnchored(segs, K);

        // Transform for right-anchored windows: [l, r] -> [-r, -l]
        vector<array<ll,3>> segs2;
        segs2.reserve(n);
        for (auto &s : segs) {
            ll l = s[0], r = s[1], c = s[2];
            segs2.push_back({-r, -l, c});
        }
        ans = max(ans, solveLeftAnchored(segs2, K));

        return ans;
    }
};
// @lc code=end
