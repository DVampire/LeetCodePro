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
        // Step 1: Build adjacency list
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }

        // Step 2: Find all suspicious methods using BFS starting from k
        vector<bool> suspicious(n, false);
        queue<int> q;
        
        suspicious[k] = true;
        q.push(k);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!suspicious[neighbor]) {
                    suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Step 3: Check if any non-suspicious method calls a suspicious one
        bool canRemove = true;
        for (const auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];
            // If caller is NOT suspicious and callee IS suspicious, we cannot remove
            if (!suspicious[u] && suspicious[v]) {
                canRemove = false;
                break;
            }
        }

        // Step 4: Return result based on removal condition
        vector<int> result;
        if (canRemove) {
            for (int i = 0; i < n; ++i) {
                if (!suspicious[i]) {
                    result.push_back(i);
                }
            }
        } else {
            result.resize(n);
            iota(result.begin(), result.end(), 0);
        }

        return result;
    }
};
# @lc code=end