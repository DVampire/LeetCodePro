#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n + 1);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int LOG = 18;
        vector<vector<int>> up(n + 1, vector<int>(LOG));
        vector<int> depth(n + 1, 0);
        vector<bool> visited(n + 1, false);
        queue<int> q;

        // Root the tree at node 1 and perform BFS to compute depths and binary lifting table
        q.push(1);
        visited[1] = true;
        depth[1] = 0;
        for (int i = 0; i < LOG; i++) up[1][i] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    depth[v] = depth[u] + 1;
                    up[v][0] = u;
                    for (int i = 1; i < LOG; i++) {
                        up[v][i] = up[up[v][i - 1]][i - 1];
                    }
                    q.push(v);
                }
            }
        }

        const int MOD = 1000000007;
        vector<int> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow2[i] = (int)((1LL * pow2[i - 1] * 2) % MOD);
        }

        vector<int> results;
        results.reserve(queries.size());
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            if (u == v) {
                results.push_back(0);
                continue;
            }

            int original_u = u, original_v = v;
            // LCA calculation using binary lifting
            if (depth[u] < depth[v]) swap(u, v);
            for (int i = LOG - 1; i >= 0; i--) {
                if (depth[u] - (1 << i) >= depth[v]) {
                    u = up[u][i];
                }
            }

            int lca;
            if (u == v) {
                lca = u;
            } else {
                for (int i = LOG - 1; i >= 0; i--) {
                    if (up[u][i] != up[v][i]) {
                        u = up[u][i];
                        v = up[v][i];
                    }
                }
                lca = up[u][0];
            }

            int dist = depth[original_u] + depth[original_v] - 2 * depth[lca];
            // For distance L > 0, number of ways is 2^(L-1)
            results.push_back(pow2[dist - 1]);
        }

        return results;
    }
};
# @lc code=end