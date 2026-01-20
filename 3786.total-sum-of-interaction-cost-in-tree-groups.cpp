#
# @lc app=leetcode id=3786 lang=cpp
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#

# @lc code=start
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        // Adjacency list for the tree
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Total count of nodes for each group
        // Groups are 1-indexed up to 20, so size 21 is enough
        vector<int> totalGroupCounts(21, 0);
        for (int g : group) {
            totalGroupCounts[g]++;
        }

        long long totalCost = 0;

        // DFS to compute subtree group counts and accumulate costs
        // Returns a vector of size 21 where index g is the count of nodes with group g in the subtree
        auto dfs = [&](auto&& self, int u, int p) -> vector<int> {
            vector<int> subtreeCounts(21, 0);
            subtreeCounts[group[u]] = 1;

            for (int v : adj[u]) {
                if (v == p) continue;
                
                vector<int> childCounts = self(self, v, u);
                
                // For the edge (u, v), calculate contribution for each group
                for (int g = 1; g <= 20; ++g) {
                    if (totalGroupCounts[g] > 0) {
                        // Contribution = (nodes of group g in subtree v) * (nodes of group g outside subtree v)
                        long long countInSubtree = childCounts[g];
                        long long countOutside = totalGroupCounts[g] - countInSubtree;
                        totalCost += countInSubtree * countOutside;
                        
                        // Merge child counts into current subtree counts
                        subtreeCounts[g] += childCounts[g];
                    }
                }
            }
            return subtreeCounts;
        };

        dfs(dfs, 0, -1);

        return totalCost;
    }
};
# @lc code=end