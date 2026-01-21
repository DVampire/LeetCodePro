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
        
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        map<tuple<int, int, int>, long long> memo;
        
        function<long long(int, int, int, int)> dfs = [&](int u, int parent, int last_inv_dist, int ancestor_parity) -> long long {
            auto key = make_tuple(u, last_inv_dist, ancestor_parity);
            if (memo.count(key)) {
                return memo[key];
            }
            
            long long result = LLONG_MIN;
            
            // Choice 1: Don't invert u
            long long sum1 = ancestor_parity == 0 ? (long long)nums[u] : -(long long)nums[u];
            for (int v : adj[u]) {
                if (v == parent) continue;
                sum1 += dfs(v, u, min(last_inv_dist + 1, k), ancestor_parity);
            }
            result = max(result, sum1);
            
            // Choice 2: Invert u (if allowed)
            if (last_inv_dist >= k) {
                int new_parity = 1 - ancestor_parity;
                long long sum2 = new_parity == 0 ? (long long)nums[u] : -(long long)nums[u];
                for (int v : adj[u]) {
                    if (v == parent) continue;
                    sum2 += dfs(v, u, 1, new_parity);
                }
                result = max(result, sum2);
            }
            
            memo[key] = result;
            return result;
        };
        
        return dfs(0, -1, k, 0);
    }
};
# @lc code=end