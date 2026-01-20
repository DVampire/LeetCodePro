#
# @lc app=leetcode id=3331 lang=cpp
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> new_parent = parent;
        // ancestors[char_index] stores the node index of the closest ancestor with that char
        vector<int> ancestors(26, -1);

        // DFS to find new parents
        auto dfs_find_parents = [&](auto&& self, int u) -> void {
            int char_idx = s[u] - 'a';
            int old_ancestor = ancestors[char_idx];

            if (old_ancestor != -1) {
                new_parent[u] = old_ancestor;
            }

            ancestors[char_idx] = u;
            for (int v : adj[u]) {
                self(self, v);
            }
            // Backtrack
            ancestors[char_idx] = old_ancestor;
        };

        dfs_find_parents(dfs_find_parents, 0);

        // Build new tree
        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            if (new_parent[i] != -1) {
                new_adj[new_parent[i]].push_back(i);
            }
        }

        vector<int> subtree_sizes(n, 0);
        // DFS to calculate subtree sizes
        auto dfs_calc_sizes = [&](auto&& self, int u) -> int {
            int size = 1;
            for (int v : new_adj[u]) {
                size += self(self, v);
            }
            subtree_sizes[u] = size;
            return size;
        };

        dfs_calc_sizes(dfs_calc_sizes, 0);

        return subtree_sizes;
    }
};
# @lc code=end