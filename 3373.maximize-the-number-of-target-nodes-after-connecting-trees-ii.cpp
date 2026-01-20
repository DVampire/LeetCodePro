#
# @lc app=leetcode id=3373 lang=cpp
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        auto getPartitions = [](int size, const vector<vector<int>>& edges) {
            vector<vector<int>> adj(size);
            for (const auto& e : edges) {
                adj[e[0]].push_back(e[1]);
                adj[e[1]].push_back(e[0]);
            }
            vector<int> color(size, -1);
            int count0 = 0;
            queue<int> q;
            q.push(0);
            color[0] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (color[u] == 0) count0++;
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                }
            }
            return make_pair(color, count0);
        };

        auto [color1, count0_1] = getPartitions(n, edges1);
        int count1_1 = n - count0_1;

        auto [color2, count0_2] = getPartitions(m, edges2);
        int maxPart2 = max(count0_2, m - count0_2);

        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = (color1[i] == 0 ? count0_1 : count1_1) + maxPart2;
        }

        return ans;
    }
};
# @lc code=end