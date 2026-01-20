#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3367 lang=cpp
 *
 * [3367] Maximize Sum of Weights after Edge Removals
 */

// @lc code=start
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = (int)edges.size() + 1;
        vector<vector<pair<int,int>>> g(n);
        g.reserve(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        vector<int> parent(n, -1);
        vector<int> order;
        order.reserve(n);

        // Build parent and traversal order iteratively
        vector<int> st;
        st.reserve(n);
        st.push_back(0);
        parent[0] = -2;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (auto [v, w] : g[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != -1) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }
        parent[0] = -1;

        vector<long long> dp0(n, 0), dp1(n, 0);

        // Post-order DP
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            long long base = 0;
            vector<long long> gains;
            gains.reserve(g[u].size());

            for (auto [v, w] : g[u]) {
                if (v == parent[u]) continue;
                base += dp0[v];
                long long gain = (long long)w + dp1[v] - dp0[v];
                if (gain > 0) gains.push_back(gain);
            }

            sort(gains.begin(), gains.end(), greater<long long>());
            int m = (int)gains.size();
            vector<long long> pref(m + 1, 0);
            for (int j = 0; j < m; ++j) pref[j + 1] = pref[j] + gains[j];

            int cap0 = k;
            int cap1 = k - 1;
            if (cap0 < 0) cap0 = 0;
            if (cap1 < 0) cap1 = 0;

            dp0[u] = base + pref[min(cap0, m)];
            dp1[u] = base + pref[min(cap1, m)];
        }

        return dp0[0];
    }
};
// @lc code=end
