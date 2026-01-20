#
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // The threshold condition is effectively satisfied if we can form a tree
        // rooted at node 0 in the reversed graph, as each node would have 
        // exactly one outgoing edge in that tree, and 1 <= threshold.
        
        vector<vector<pair<int, int>>> adj(n);
        int max_w = 0;
        for (const auto& edge : edges) {
            // Reverse the edges: Ai -> Bi becomes Bi -> Ai
            adj[edge[1]].push_back({edge[0], edge[2]});
            max_w = max(max_w, edge[2]);
        }

        auto check = [&](int limit) {
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(0);
            visited[0] = true;
            int count = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (w <= limit && !visited[v]) {
                        visited[v] = true;
                        count++;
                        q.push(v);
                    }
                }
            }
            return count == n;
        };

        int low = 1, high = max_w, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
# @lc code=end