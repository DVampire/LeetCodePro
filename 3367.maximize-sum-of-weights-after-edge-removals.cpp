#
# @lc app=leetcode id=3367 lang=cpp
#
# [3367] Maximize Sum of Weights after Edge Removals
#
# @lc code=start
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> adj(n);
        
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        function<pair<long long, long long>(int, int)> dfs = [&](int node, int parent) -> pair<long long, long long> {
            vector<long long> gains;
            long long base = 0;
            
            for (auto& p : adj[node]) {
                int child = p.first;
                int weight = p.second;
                if (child == parent) continue;
                
                pair<long long, long long> result = dfs(child, node);
                long long dp0_child = result.first;
                long long dp1_child = result.second;
                
                base += dp0_child;
                long long gain = weight + dp1_child - dp0_child;
                gains.push_back(gain);
            }
            
            sort(gains.rbegin(), gains.rend());
            
            // dp0: can use at most k edges
            long long dp0 = base;
            for (int i = 0; i < min((int)gains.size(), k); i++) {
                if (gains[i] > 0) {
                    dp0 += gains[i];
                }
            }
            
            // dp1: can use at most k-1 edges
            long long dp1 = base;
            for (int i = 0; i < min((int)gains.size(), k - 1); i++) {
                if (gains[i] > 0) {
                    dp1 += gains[i];
                }
            }
            
            return {dp0, dp1};
        };
        
        pair<long long, long long> result = dfs(0, -1);
        return result.first;
    }
};
# @lc code=end