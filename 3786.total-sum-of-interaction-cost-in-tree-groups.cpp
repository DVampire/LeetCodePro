#
# @lc app=leetcode id=3786 lang=cpp
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#
# @lc code=start
class Solution {
private:
    void dfs(int node, int parent, vector<vector<int>>& adj, vector<int>& group, vector<int>& countV, vector<bool>& visited) {
        visited[node] = true;
        countV[group[node]]++;
        for (int neighbor : adj[node]) {
            if (neighbor != parent && !visited[neighbor]) {
                dfs(neighbor, node, adj, group, countV, visited);
            }
        }
    }
    
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        long long totalCost = 0;
        vector<int> totalCount(21, 0);
        for (int i = 0; i < n; i++) {
            totalCount[group[i]]++;
        }
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            vector<int> countV(21, 0);
            vector<bool> visited(n, false);
            dfs(v, u, adj, group, countV, visited);
            
            for (int g = 1; g <= 20; g++) {
                int countU = totalCount[g] - countV[g];
                totalCost += (long long)countU * countV[g];
            }
        }
        
        return totalCost;
    }
};
# @lc code=end