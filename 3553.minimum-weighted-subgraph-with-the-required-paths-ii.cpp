#
# @lc app=leetcode id=3553 lang=cpp
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        vector<int> depth(n, 0);
        vector<long long> dist(n, 0);
        vector<vector<int>> up(n, vector<int>(18, 0));
        vector<int> parent(n, -1);
        
        vector<int> q;
        q.reserve(n);
        q.push_back(0);
        parent[0] = 0;
        depth[0] = 0;
        dist[0] = 0;
        up[0][0] = 0;

        int head = 0;
        while (head < q.size()) {
            int u = q[head++];
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (v != parent[u]) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + w;
                    up[v][0] = u;
                    q.push_back(v);
                }
            }
        }

        for (int j = 1; j < 18; j++) {
            for (int i = 0; i < n; i++) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        auto get_lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            for (int i = 17; i >= 0; i--) {
                if (depth[u] - (1 << i) >= depth[v]) {
                    u = up[u][i];
                }
            }
            if (u == v) return u;
            for (int i = 17; i >= 0; i--) {
                if (up[u][i] != up[v][i]) {
                    u = up[u][i];
                    v = up[v][i];
                }
            }
            return up[u][0];
        };

        auto get_dist = [&](int u, int v) {
            return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
        };

        vector<int> results;
        results.reserve(queries.size());
        for (const auto& query : queries) {
            int u = query[0], v = query[1], w = query[2];
            long long d_uv = get_dist(u, v);
            long long d_vw = get_dist(v, w);
            long long d_uw = get_dist(u, w);
            results.push_back((int)((d_uv + d_vw + d_uw) / 2));
        }

        return results;
    }
};
# @lc code=end