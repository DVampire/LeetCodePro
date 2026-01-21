#
# @lc app=leetcode id=3544 lang=cpp
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        
        // Build adjacency list
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // Memoization: memo[node][dist][parity]
        const long long NEG_INF = LLONG_MIN / 2;
        vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(k + 1, vector<long long>(2, NEG_INF)));
        
        function<long long(int, int, int, int)> dfs = [&](int node, int parent, int dist, int parity) -> long long {
            // Check memoization
            if (memo[node][dist][parity] != NEG_INF) {
                return memo[node][dist][parity];
            }
            
            long long result = NEG_INF;
            
            // Option 1: Don't invert this node
            long long sum = (parity == 0) ? nums[node] : -nums[node];
            for (int child : adj[node]) {
                if (child != parent) {
                    sum += dfs(child, node, min(dist + 1, k), parity);
                }
            }
            result = max(result, sum);
            
            // Option 2: Invert this node (only if dist >= k)
            if (dist >= k) {
                sum = (parity == 1) ? nums[node] : -nums[node];
                for (int child : adj[node]) {
                    if (child != parent) {
                        sum += dfs(child, node, 1, 1 - parity);
                    }
                }
                result = max(result, sum);
            }
            
            memo[node][dist][parity] = result;
            return result;
        };
        
        return dfs(0, -1, k, 0);
    }
};
# @lc code=end