#include <vector>
#include <algorithm>

using namespace std;

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
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        auto dfs = [&](auto self, int u, int p) -> pair<long long, long long> {
            long long total_sum = 0;
            vector<long long> diffs;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (v == p) continue;

                auto [res0, res1] = self(self, v, u);
                total_sum += res0;
                long long diff = (res1 + w) - res0;
                if (diff > 0) {
                    diffs.push_back(diff);
                }
            }

            sort(diffs.rbegin(), diffs.rend());

            long long take_k = total_sum;
            long long take_k_minus_1 = total_sum;

            for (int i = 0; i < diffs.size(); ++i) {
                if (i < k) take_k += diffs[i];
                if (i < k - 1) take_k_minus_1 += diffs[i];
            }

            return {take_k, take_k_minus_1};
        };

        return dfs(dfs, 0, -1).first;
    }
};
# @lc code=end