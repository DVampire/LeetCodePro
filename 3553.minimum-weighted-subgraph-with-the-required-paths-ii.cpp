#
# @lc app=leetcode id=3553 lang=cpp
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#
# @lc code=start
class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        
        // Function to compute distances from a source node to all other nodes using DFS
        auto computeDistances = [&](int src) {
            vector<long long> dist(n, -1);
            function<void(int, int, long long)> dfs = [&](int u, int parent, long long d) {
                dist[u] = d;
                for (auto [v, w] : graph[u]) {
                    if (v != parent) {
                        dfs(v, u, d + w);
                    }
                }
            };
            dfs(src, -1, 0);
            return dist;
        };
        
        vector<int> result;
        
        for (auto& query : queries) {
            int src1 = query[0], src2 = query[1], dest = query[2];
            
            // Compute distances from src1, src2, and dest to all nodes
            vector<long long> dist1 = computeDistances(src1);
            vector<long long> dist2 = computeDistances(src2);
            vector<long long> distDest = computeDistances(dest);
            
            // Find the Steiner point that minimizes the sum
            long long minWeight = LLONG_MAX;
            for (int i = 0; i < n; i++) {
                minWeight = min(minWeight, dist1[i] + dist2[i] + distDest[i]);
            }
            
            result.push_back((int)minWeight);
        }
        
        return result;
    }
};
# @lc code=end