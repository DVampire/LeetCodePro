#
# @lc app=leetcode id=3373 lang=cpp
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        // Helper lambda to build adjacency list and compute bipartition counts
        auto processTree = [](const vector<vector<int>>& edges, int n, vector<int>& colors) -> vector<int> {
            vector<vector<int>> adj(n);
            for (const auto& edge : edges) {
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]);
            }
            
            vector<int> counts(2, 0);
            // BFS or DFS to color. Let's use BFS to avoid recursion depth issues.
            // Node 0 is color 0.
            colors[0] = 0;
            counts[0]++;
            
            vector<int> q;
            q.reserve(n);
            q.push_back(0);
            
            int head = 0;
            while(head < q.size()){
                int u = q[head++];
                int c = colors[u];
                int next_c = 1 - c;
                
                for(int v : adj[u]){
                    if(colors[v] == -1){
                        colors[v] = next_c;
                        counts[next_c]++;
                        q.push_back(v);
                    }
                }
            }
            return counts;
        };

        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        vector<int> colors1(n, -1);
        vector<int> counts1 = processTree(edges1, n, colors1);

        vector<int> colors2(m, -1);
        vector<int> counts2 = processTree(edges2, m, colors2);

        // The max contribution from Tree 2 is the size of the larger partition set.
        // If we connect to a node of color 0 in Tree 2, we get all nodes of color 1 in Tree 2 as targets.
        // If we connect to a node of color 1 in Tree 2, we get all nodes of color 0 in Tree 2 as targets.
        // We can choose which node in Tree 2 to connect to, so we choose the one that gives max targets.
        int max_from_tree2 = max(counts2[0], counts2[1]);

        vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            // For node i in Tree 1, its own tree contributes nodes of the same color.
            int from_tree1 = counts1[colors1[i]];
            result[i] = from_tree1 + max_from_tree2;
        }

        return result;
    }
};
# @lc code=end