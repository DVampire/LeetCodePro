#
# @lc app=leetcode id=3373 lang=cpp
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        
        // Build adjacency lists
        vector<vector<int>> graph1(n), graph2(m);
        for (auto& e : edges1) {
            graph1[e[0]].push_back(e[1]);
            graph1[e[1]].push_back(e[0]);
        }
        for (auto& e : edges2) {
            graph2[e[0]].push_back(e[1]);
            graph2[e[1]].push_back(e[0]);
        }
        
        // Color tree1 using BFS
        vector<int> color1(n, -1);
        color1[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph1[u]) {
                if (color1[v] == -1) {
                    color1[v] = 1 - color1[u];
                    q.push(v);
                }
            }
        }
        
        // Count colors in tree1
        int count0_tree1 = 0, count1_tree1 = 0;
        for (int c : color1) {
            if (c == 0) count0_tree1++;
            else count1_tree1++;
        }
        
        // Color tree2 using BFS
        vector<int> color2(m, -1);
        color2[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph2[u]) {
                if (color2[v] == -1) {
                    color2[v] = 1 - color2[u];
                    q.push(v);
                }
            }
        }
        
        // Count colors in tree2
        int count0_tree2 = 0, count1_tree2 = 0;
        for (int c : color2) {
            if (c == 0) count0_tree2++;
            else count1_tree2++;
        }
        
        int max_from_tree2 = max(count0_tree2, count1_tree2);
        
        // Build result
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            if (color1[i] == 0) {
                result[i] = count0_tree1 + max_from_tree2;
            } else {
                result[i] = count1_tree1 + max_from_tree2;
            }
        }
        
        return result;
    }
};
# @lc code=end