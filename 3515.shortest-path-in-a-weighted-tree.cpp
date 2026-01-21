#
# @lc app=leetcode id=3515 lang=cpp
#
# [3515] Shortest Path in a Weighted Tree
#
# @lc code=start
class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Build adjacency list with edge indices
        vector<vector<pair<int, int>>> adj(n + 1);
        map<pair<int, int>, int> edgeIndex;
        
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            
            edgeIndex[{min(u, v), max(u, v)}] = i;
        }
        
        vector<int> edgeWeights(edges.size());
        for (int i = 0; i < edges.size(); i++) {
            edgeWeights[i] = edges[i][2];
        }
        
        vector<int> result;
        
        for (const auto& query : queries) {
            if (query[0] == 1) {
                int u = query[1];
                int v = query[2];
                int w = query[3];
                
                int idx = edgeIndex[{min(u, v), max(u, v)}];
                edgeWeights[idx] = w;
            } else {
                int target = query[1];
                vector<bool> visited(n + 1, false);
                int dist = dfs(1, target, adj, edgeWeights, visited);
                result.push_back(dist);
            }
        }
        
        return result;
    }
    
private:
    int dfs(int node, int target, const vector<vector<pair<int, int>>>& adj, 
            const vector<int>& edgeWeights, vector<bool>& visited) {
        if (node == target) {
            return 0;
        }
        
        visited[node] = true;
        
        for (const auto& p : adj[node]) {
            int neighbor = p.first;
            int edgeIdx = p.second;
            if (!visited[neighbor]) {
                int dist = dfs(neighbor, target, adj, edgeWeights, visited);
                if (dist >= 0) {
                    return dist + edgeWeights[edgeIdx];
                }
            }
        }
        
        return -1;
    }
};
# @lc code=end