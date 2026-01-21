#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, long long>>> adj(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            long long w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        const int LOG = 18;
        vector<vector<int>> parent(LOG, vector<int>(n, -1));
        vector<vector<long long>> dist_up(LOG, vector<long long>(n, 0));
        vector<long long> dist_root(n, 0);
        vector<int> dep(n, 0);

        // BFS to compute dist_root, dep, parent[0]
        vector<bool> vis(n, false);
        queue<int> qu;
        vis[0] = true;
        parent[0][0] = -1;
        dist_root[0] = 0;
        dep[0] = 0;
        qu.push(0);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for (auto [v, w] : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    parent[0][v] = u;
                    dist_root[v] = dist_root[u] + w;
                    dep[v] = dep[u] + 1;
                    qu.push(v);
                }
            }
        }

        // Compute dist_up[0]
        for (int u = 0; u < n; ++u) {
            int p = parent[0][u];
            if (p != -1) {
                dist_up[0][u] = dist_root[u] - dist_root[p];
            }
        }

        // Fill binary lifting tables
        for (int k = 1; k < LOG; ++k) {
            for (int u = 0; u < n; ++u) {
                int mid = parent[k - 1][u];
                if (mid != -1) {
                    parent[k][u] = parent[k - 1][mid];
                    dist_up[k][u] = dist_up[k - 1][u] + dist_up[k - 1][mid];
                } else {
                    parent[k][u] = -1;
                    dist_up[k][u] = 0;
                }
            }
        }

        // LCA lambda
        auto get_lca = [&](int u, int v) -> int {
            if (dep[u] > dep[v]) swap(u, v);
            int diff = dep[v] - dep[u];
            for (int k = 0; k < LOG; ++k) {
                if (diff & (1 << k)) {
                    v = parent[k][v];
                }
            }
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; --k) {
                if (parent[k][u] != parent[k][v]) {
                    u = parent[k][u];
                    v = parent[k][v];
                }
            }
            return parent[0][u];
        };

        // Lift strict less for up case
        auto lift_strict_less = [&](int node, long long target_dist) -> int {
            int x = node;
            long long rem = target_dist;
            for (int k = LOG - 1; k >= 0; --k) {
                if (parent[k][x] != -1 && dist_up[k][x] < rem) {
                    rem -= dist_up[k][x];
                    x = parent[k][x];
                }
            }
            return x;
        };

        // Lift <= for down case
        auto lift_leq = [&](int node, long long max_dist) -> int {
            int x = node;
            long long rem = max_dist;
            for (int k = LOG - 1; k >= 0; --k) {
                if (parent[k][x] != -1 && dist_up[k][x] <= rem) {
                    rem -= dist_up[k][x];
                    x = parent[k][x];
                }
            }
            return x;
        };

        vector<int> ans;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(u);
                continue;
            }
            int l = get_lca(u, v);
            long long du = dist_root[u] - dist_root[l];
            long long dv_ = dist_root[v] - dist_root[l];
            long long total = du + dv_;
            long long target = (total + 1LL) / 2;
            int med;
            if (du >= target) {
                // Up path
                int y = lift_strict_less(u, target);
                med = parent[0][y];
            } else {
                // Down path
                long long need = target - du;
                long long maxd_from_v = dv_ - need;
                int y = lift_leq(v, maxd_from_v);
                med = y;
            }
            ans.push_back(med);
        }
        return ans;
    }
};
# @lc code=end