#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
class Solution {
public:
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<int> pow2;
    int LOG;
    const int MOD = 1e9 + 7;

    void dfs(int u, int p, int d) {
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < LOG; i++) {
            if (up[u][i-1] != -1)
                up[u][i] = up[up[u][i-1]][i-1];
            else
                up[u][i] = -1;
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        adj.assign(n + 1, vector<int>());
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        
        up.assign(n + 1, vector<int>(LOG, -1));
        depth.assign(n + 1, 0);

        dfs(1, -1, 0);

        // Precompute powers of 2
        // Max path length is n-1, so we need up to 2^(n-2)
        pow2.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            pow2[i] = (1LL * pow2[i-1] * 2) % MOD;
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            int lca = get_lca(u, v);
            int dist = depth[u] + depth[v] - 2 * depth[lca];
            
            // If path length is L, number of ways is 2^(L-1)
            // dist is guaranteed > 0 here
            ans.push_back(pow2[dist - 1]);
        }

        return ans;
    }
};
# @lc code=end