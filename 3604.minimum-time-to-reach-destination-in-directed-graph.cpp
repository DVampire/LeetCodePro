//
// @lc app=leetcode id=3604 lang=cpp
//
// [3604] Minimum Time to Reach Destination in Directed Graph
//

// @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<vector<array<int, 3>>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2], edge[3]});
        }
        
        vector<long long> dist(n, LLONG_MAX);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        dist[0] = 0;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            long long t = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (t > dist[u]) continue;
            
            if (u == n - 1) return (int)t;
            
            for (auto& e : adj[u]) {
                int v = e[0], start = e[1], end = e[2];
                if (t > end) continue;
                
                long long arrival = (t >= start) ? t + 1 : (long long)start + 1;
                
                if (arrival < dist[v]) {
                    dist[v] = arrival;
                    pq.push({arrival, v});
                }
            }
        }
        
        return -1;
    }
};
// @lc code=end