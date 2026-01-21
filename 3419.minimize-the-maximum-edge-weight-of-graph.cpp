#
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#
# @lc code=start
class Solution {
public:
    bool canReach(int n, vector<vector<int>>& edges, int maxWeight, int threshold) {
        vector<vector<pair<int, int>>> adj(n);
        
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (w <= maxWeight) {
                adj[u].push_back({v, w});
            }
        }
        
        for (int i = 0; i < n; i++) {
            if ((int)adj[i].size() > threshold) {
                sort(adj[i].begin(), adj[i].end(), 
                     [](const auto& a, const auto& b) {
                         return a.second < b.second;
                     });
                adj[i].resize(threshold);
            }
        }
        
        for (int start = 1; start < n; start++) {
            queue<int> q;
            vector<bool> visited(n, false);
            q.push(start);
            visited[start] = true;
            bool found = false;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                if (u == 0) {
                    found = true;
                    break;
                }
                
                for (const auto& [v, w] : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            
            if (!found) return false;
        }
        
        return true;
    }
    
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        if (edges.empty()) return -1;
        
        set<int> weights;
        for (const auto& e : edges) {
            weights.insert(e[2]);
        }
        
        vector<int> sortedWeights(weights.begin(), weights.end());
        
        int left = 0, right = sortedWeights.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int maxWeight = sortedWeights[mid];
            
            if (canReach(n, edges, maxWeight, threshold)) {
                result = maxWeight;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};
# @lc code=end