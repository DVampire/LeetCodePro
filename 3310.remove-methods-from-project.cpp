#
# @lc app=leetcode id=3310 lang=cpp
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Step 1: Build the graph
        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Step 2: Identify all suspicious methods (reachable from k)
        // Use a boolean vector for fast lookups
        vector<bool> isSuspicious(n, false);
        queue<int> q;
        
        q.push(k);
        isSuspicious[k] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!isSuspicious[v]) {
                    isSuspicious[v] = true;
                    q.push(v);
                }
            }
        }
        
        // Step 3: Check if any non-suspicious method invokes a suspicious method
        bool canRemove = true;
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            
            // If u is NOT suspicious but v IS suspicious, we cannot remove the group
            if (!isSuspicious[u] && isSuspicious[v]) {
                canRemove = false;
                break;
            }
        }
        
        // Step 4: Construct the result
        vector<int> result;
        if (canRemove) {
            // Return only non-suspicious methods
            for (int i = 0; i < n; ++i) {
                if (!isSuspicious[i]) {
                    result.push_back(i);
                }
            }
        } else {
            // Return all methods
            for (int i = 0; i < n; ++i) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};
# @lc code=end