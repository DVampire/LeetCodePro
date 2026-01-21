//
// @lc app=leetcode id=3425 lang=cpp
//
// [3425] Longest Special Path
//

// @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        
        // Build adjacency list
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        // last_occ[val] = depth where val was last seen in current path
        unordered_map<int, int> last_occ;
        // Distance prefix sums from root
        vector<long long> dist = {0};
        
        long long max_length = 0;
        int min_nodes = 1;
        
        function<void(int, int, int, int)> dfs = [&](int u, int parent, int depth, int left_bound) {
            int val = nums[u];
            
            // Save previous occurrence and update left_bound if needed
            int prev_occ = -1;
            auto it = last_occ.find(val);
            if (it != last_occ.end()) {
                prev_occ = it->second;
                left_bound = max(left_bound, prev_occ + 1);
            }
            last_occ[val] = depth;
            
            // Calculate path metrics from left_bound to current depth
            long long path_length = dist[depth] - dist[left_bound];
            int path_nodes = depth - left_bound + 1;
            
            // Update answer
            if (path_length > max_length || (path_length == max_length && path_nodes < min_nodes)) {
                max_length = path_length;
                min_nodes = path_nodes;
            }
            
            // DFS to children
            for (auto& [v, w] : adj[u]) {
                if (v != parent) {
                    dist.push_back(dist.back() + w);
                    dfs(v, u, depth + 1, left_bound);
                    dist.pop_back();
                }
            }
            
            // Restore state for backtracking
            if (prev_occ == -1) {
                last_occ.erase(val);
            } else {
                last_occ[val] = prev_occ;
            }
        };
        
        dfs(0, -1, 0, 0);
        
        return {(int)max_length, min_nodes};
    }
};
// @lc code=end