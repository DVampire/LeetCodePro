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
        
        function<pair<long long, long long>(int, int)> dfs = [&](int u, int parent) -> pair<long long, long long> {
            vector<long long> gains;
            long long base = 0;
            
            for (auto& [v, w] : adj[u]) {
                if (v == parent) continue;
                auto [child0, child1] = dfs(v, u);
                base += child0;
                long long gain = w + child1 - child0;
                gains.push_back(gain);
            }
            
            sort(gains.rbegin(), gains.rend());
            
            long long res0 = base, res1 = base;
            
            for (int i = 0; i < (int)gains.size() && gains[i] > 0; i++) {
                if (i < k) res0 += gains[i];
                if (i < k - 1) res1 += gains[i];
            }
            
            return {res0, res1};
        };
        
        return dfs(0, -1).first;
    }
};
# @lc code=end