#
# @lc app=leetcode id=3310 lang=cpp
#
# [3310] Remove Methods From Project
#

# @lc code=start
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }

        // Find all suspicious methods using BFS starting from k
        vector<bool> isSuspicious(n, false);
        queue<int> q;
        q.push(k);
        isSuspicious[k] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (int neighbor : adj[curr]) {
                if (!isSuspicious[neighbor]) {
                    isSuspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Check if any non-suspicious method invokes a suspicious method
        bool canRemove = true;
        for (const auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];
            if (!isSuspicious[u] && isSuspicious[v]) {
                canRemove = false;
                break;
            }
        }

        // Prepare the result list
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
            result.resize(n);
            iota(result.begin(), result.end(), 0);
        }

        return result;
    }
};
# @lc code=end