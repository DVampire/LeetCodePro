#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3515 lang=cpp
//
// [3515] Shortest Path in a Weighted Tree
//

// @lc code=start
class Solution {
    struct BIT {
        int n;
        vector<long long> bit;
        BIT(int n = 0) { init(n); }
        void init(int n_) {
            n = n_;
            bit.assign(n + 2, 0);
        }
        void add(int i, long long delta) {
            for (; i <= n; i += i & -i) bit[i] += delta;
        }
        long long sumPrefix(int i) const {
            long long s = 0;
            for (; i > 0; i -= i & -i) s += bit[i];
            return s;
        }
        void rangeAdd(int l, int r, long long delta) {
            if (l > r) return;
            add(l, delta);
            if (r + 1 <= n) add(r + 1, -delta);
        }
        long long pointQuery(int i) const {
            return sumPrefix(i);
        }
    };

    static long long keyEdge(int u, int v) {
        if (u > v) swap(u, v);
        // 1e5 < 2^17, shift by 20 is safe.
        return (static_cast<long long>(u) << 20) | static_cast<long long>(v);
    }

public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int m = (int)edges.size();
        vector<vector<array<int,3>>> adj(n + 1);
        vector<int> edgeW(m);
        unordered_map<long long, int> eid;
        eid.reserve((size_t)m * 2 + 10);
        eid.max_load_factor(0.7f);

        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            edgeW[i] = w;
            adj[u].push_back({v, w, i});
            adj[v].push_back({u, w, i});
            eid[keyEdge(u, v)] = i;
        }

        vector<int> parent(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0);
        vector<long long> dist0(n + 1, 0);
        vector<int> childOfEdge(m, 0);

        // Iterative DFS for Euler tour and initial distances
        int timer = 0;
        struct Frame { int u, p; long long d; int state; };
        vector<Frame> st;
        st.reserve(2 * n);
        st.push_back({1, 0, 0LL, 0});
        parent[1] = 0;

        while (!st.empty()) {
            auto cur = st.back();
            st.pop_back();
            int u = cur.u, p = cur.p;
            if (cur.state == 0) {
                tin[u] = ++timer;
                dist0[u] = cur.d;
                parent[u] = p;

                st.push_back({u, p, cur.d, 1});
                // push children
                for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                    auto [v, w, id] = adj[u][i];
                    if (v == p) continue;
                    // orient edge id so that child is v
                    childOfEdge[id] = v;
                    st.push_back({v, u, cur.d + (long long)w, 0});
                }
            } else {
                tout[u] = timer;
            }
        }

        BIT bit(n);
        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2], wNew = q[3];
                int id = eid[keyEdge(u, v)];
                long long delta = (long long)wNew - (long long)edgeW[id];
                if (delta != 0) {
                    edgeW[id] = wNew;
                    int child = childOfEdge[id];
                    bit.rangeAdd(tin[child], tout[child], delta);
                }
            } else {
                int x = q[1];
                long long res = dist0[x] + bit.pointQuery(tin[x]);
                ans.push_back((int)res);
            }
        }

        return ans;
    }
};
// @lc code=end
