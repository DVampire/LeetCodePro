#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
public:
    const int MOD = 1e9 + 7;
    
    int findPathLength(int u, int v, vector<vector<int>>& adj, int n) {
        if (u == v) return 0;
        
        vector<int> parent(n + 1, -1);
        queue<int> q;
        q.push(u);
        parent[u] = u;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            if (node == v) break;
            
            for (int neighbor : adj[node]) {
                if (parent[neighbor] == -1) {
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }
        
        int length = 0;
        int curr = v;
        while (curr != u) {
            length++;
            curr = parent[curr];
        }
        return length;
    }
    
    long long power(long long base, long long exp, long long mod) {
        long long result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
    
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n + 1);
        
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<int> result;
        for (auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            int edgeCount = findPathLength(u, v, adj, n);
            
            if (edgeCount == 0) {
                result.push_back(0);
            } else {
                long long ans = power(2, edgeCount - 1, MOD);
                result.push_back(ans);
            }
        }
        
        return result;
    }
};
# @lc code=end