#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3585 lang=cpp
//
// [3585] Find Weighted Median Node in Tree
//

// @lc code=start
class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<int> depth(n, 0);
        vector<long long> distRoot(n, 0);
        vector<int> par(n, -1);
        vector<long long> wPar(n, 0);

        // Iterative DFS from root 0
        vector<int> st;
        st.reserve(n);
        st.push_back(0);
        par[0] = -1;
        depth[0] = 0;
        distRoot[0] = 0;
        wPar[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (auto [v, w] : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u;
                wPar[v] = w;
                depth[v] = depth[u] + 1;
                distRoot[v] = distRoot[u] + (long long)w;
                st.push_back(v);
            }
        }

        vector<vector<int>> up(LOG, vector<int>(n, -1));
        vector<vector<long long>> wup(LOG, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            up[0][i] = par[i];
            wup[0][i] = wPar[i];
        }
        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < n; v++) {
                int mid = up[k-1][v];
                if (mid == -1) {
                    up[k][v] = -1;
                    wup[k][v] = wup[k-1][v];
                } else {
                    up[k][v] = up[k-1][mid];
                    wup[k][v] = wup[k-1][v] + wup[k-1][mid];
                }
            }
        }

        auto lca = [&](int a, int b) -> int {
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int k = 0; k < LOG; k++) {
                if (diff & (1 << k)) a = up[k][a];
            }
            if (a == b) return a;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][a] != up[k][b]) {
                    a = up[k][a];
                    b = up[k][b];
                }
            }
            return up[0][a];
        };

        // Case A helper: on u->ancestor direction, find first node with dist(u, x) >= T
        auto firstUpAtLeast = [&](int u, long long T) -> int {
            if (T <= 0) return u;
            long long acc = 0;
            int node = u;
            for (int k = LOG - 1; k >= 0; k--) {
                int anc = up[k][node];
                if (anc != -1 && acc + wup[k][node] < T) {
                    acc += wup[k][node];
                    node = anc;
                }
            }
            return up[0][node];
        };

        // Case B helper: a is ancestor of v. Find highest node on path a->v with dist(a,node) >= need.
        auto highestWithPrefixAtLeast = [&](int v, int a, long long need) -> int {
            int node = v;
            for (int k = LOG - 1; k >= 0; k--) {
                int anc = up[k][node];
                if (anc == -1) continue;
                if (depth[anc] < depth[a]) continue;
                long long pref = distRoot[anc] - distRoot[a];
                if (pref >= need) node = anc;
            }
            return node;
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(u);
                continue;
            }
            int L = lca(u, v);
            long long total = distRoot[u] + distRoot[v] - 2LL * distRoot[L];
            long long T = (total + 1) / 2; // ceil(total/2)
            if (T == 0) {
                ans.push_back(u);
                continue;
            }

            long long du = distRoot[u] - distRoot[L];
            if (T <= du) {
                ans.push_back(firstUpAtLeast(u, T));
            } else {
                long long need = T - du;
                ans.push_back(highestWithPrefixAtLeast(v, L, need));
            }
        }
        return ans;
    }
};
// @lc code=end
