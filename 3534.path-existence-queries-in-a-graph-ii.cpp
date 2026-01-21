#
# @lc app=leetcode id=3534 lang=cpp
#
# [3534] Path Existence Queries in a Graph II
#
# @lc code=start
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());
        vector<int> position(n);
        for (int k = 0; k < n; ++k) {
            position[sorted_nodes[k].second] = k;
        }
        vector<int> component(n);
        int current_comp = 0;
        if (n > 0) {
            component[0] = 0;
            for (int k = 1; k < n; ++k) {
                if (sorted_nodes[k].first - sorted_nodes[k - 1].first > maxDiff) {
                    ++current_comp;
                }
                component[k] = current_comp;
            }
        }
        vector<int> ans;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            int pu = position[u], pv = position[v];
            int cu = component[pu], cv = component[pv];
            if (cu != cv) {
                ans.push_back(-1);
                continue;
            }
            int delta = abs(nums[u] - nums[v]);
            if (delta == 0) {
                ans.push_back(1);
            } else {
                long long ce = ((long long)delta + maxDiff - 1) / maxDiff;
                ans.push_back((int)ce);
            }
        }
        return ans;
    }
};
# @lc code=end