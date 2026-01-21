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
        vector<vector<int>> adj1(n), adj2(m);
        for (auto& e : edges1) {
            adj1[e[0]].push_back(e[1]);
            adj1[e[1]].push_back(e[0]);
        }
        for (auto& e : edges2) {
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }
        
        // Function to compute parities using BFS
        auto computeParity = [](vector<vector<int>>& adj, int nodes) {
            vector<int> parity(nodes, -1);
            queue<int> q;
            q.push(0);
            parity[0] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (parity[v] == -1) {
                        parity[v] = 1 - parity[u];
                        q.push(v);
                    }
                }
            }
            return parity;
        };
        
        vector<int> parity1 = computeParity(adj1, n);
        vector<int> parity2 = computeParity(adj2, m);
        
        // Count parities for tree 1
        int count1[2] = {0, 0};
        for (int i = 0; i < n; i++) {
            count1[parity1[i]]++;
        }
        
        // Count parities for tree 2 and find max
        int count2[2] = {0, 0};
        for (int i = 0; i < m; i++) {
            count2[parity2[i]]++;
        }
        int maxTree2 = max(count2[0], count2[1]);
        
        // Compute answer
        vector<int> answer(n);
        for (int i = 0; i < n; i++) {
            answer[i] = count1[parity1[i]] + maxTree2;
        }
        
        return answer;
    }
};
# @lc code=end