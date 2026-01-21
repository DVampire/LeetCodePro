#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#
# @lc code=start
class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Build adjacency list
        vector<vector<pair<int, long long>>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            long long w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int start = query[0], end = query[1];
            
            // Find path from start to end using BFS
            vector<int> parent(n, -1);
            vector<long long> parent_weight(n, 0);
            queue<int> q;
            vector<bool> visited(n, false);
            
            q.push(start);
            visited[start] = true;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                if (u == end) break;
                
                for (auto [v, w] : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        parent[v] = u;
                        parent_weight[v] = w;
                        q.push(v);
                    }
                }
            }
            
            // Reconstruct path from end to start
            vector<int> path;
            vector<long long> weights;
            
            int curr = end;
            while (curr != start) {
                path.push_back(curr);
                weights.push_back(parent_weight[curr]);
                curr = parent[curr];
            }
            path.push_back(start);
            
            // Reverse to get path from start to end
            reverse(path.begin(), path.end());
            reverse(weights.begin(), weights.end());
            
            // Calculate total weight
            long long total_weight = 0;
            for (auto w : weights) {
                total_weight += w;
            }
            
            // Find weighted median
            long long cumulative = 0;
            int median = start;
            
            for (int i = 0; i < path.size(); i++) {
                if (i > 0) {
                    cumulative += weights[i - 1];
                }
                if (2 * cumulative >= total_weight) {
                    median = path[i];
                    break;
                }
            }
            
            result.push_back(median);
        }
        
        return result;
    }
};
# @lc code=end