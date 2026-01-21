#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        const int MOD = 1e9 + 7;
        
        // Build adjacency list
        vector<vector<int>> adj(n + 1);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        // Preprocess: compute depth and parent for LCA
        int LOG = 20;
        vector<int> depth(n + 1, 0);
        vector<vector<int>> parent(n + 1, vector<int>(LOG, 0));
        
        // DFS to compute depth and direct parent
        function<void(int, int)> dfs = [&](int u, int p) {
            parent[u][0] = p;
            for (int v : adj[u]) {
                if (v != p) {
                    depth[v] = depth[u] + 1;
                    dfs(v, u);
                }
            }
        };
        
        dfs(1, 0);
        
        // Binary lifting preprocessing
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                if (parent[i][j-1] != 0) {
                    parent[i][j] = parent[parent[i][j-1]][j-1];
                }
            }
        }
        
        // LCA function
        auto lca = [&](int u, int v) -> int {
            if (depth[u] < depth[v]) swap(u, v);
            
            // Bring u to the same level as v
            int diff = depth[u] - depth[v];
            for (int i = 0; i < LOG; i++) {
                if ((diff >> i) & 1) {
                    u = parent[u][i];
                }
            }
            
            if (u == v) return u;
            
            // Binary search for LCA
            for (int i = LOG - 1; i >= 0; i--) {
                if (parent[u][i] != parent[v][i]) {
                    u = parent[u][i];
                    v = parent[v][i];
                }
            }
            
            return parent[u][0];
        };
        
        // Precompute powers of 2
        vector<long long> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; i++) {
            pow2[i] = (pow2[i-1] * 2) % MOD;
        }
        
        vector<int> result;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            
            if (u == v) {
                result.push_back(0);
                continue;
            }
            
            int l = lca(u, v);
            int pathLen = depth[u] + depth[v] - 2 * depth[l];
            
            result.push_back(pow2[pathLen - 1]);
        }
        
        return result;
    }
};
# @lc code=end