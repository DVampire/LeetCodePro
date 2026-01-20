#
# @lc app=leetcode id=3604 lang=cpp
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        struct Edge {
            int to, start, end;
        };
        
        // Build adjacency list for the directed graph
        vector<vector<Edge>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2], e[3]});
        }

        // Standard Dijkstra's distance array
        // Max possible time is approx 1e9 + 1e5, so 2e9 is a safe infinity
        vector<int> dist(n, 2000000000); 
        dist[0] = 0;
        
        // Min-heap for Dijkstra's: {time, node}
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // If we already found a better way to reach u, skip
            if (d > dist[u]) continue;
            // If we reached the destination, return the current minimum time
            if (u == n - 1) return d;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int s = edge.start;
                int e = edge.end;

                // The earliest time we can start traversing this edge is max(current_time, edge_start)
                int wait_until = max(d, s);
                
                // Check if the edge is still available at or after the earliest possible start time
                if (wait_until <= e) {
                    // Arrive at the destination node v at time wait_until + 1
                    if (wait_until + 1 < dist[v]) {
                        dist[v] = wait_until + 1;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        // If node n-1 is unreachable
        return -1;
    }
};
# @lc code=end