#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#
# @lc app=leetcode id=3604 lang=cpp
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
class Solution {
    struct Edge {
        int to;
        int start;
        int end;
    };

public:
    int minTime(int n, vector<vector<int>>& edges) {
        // Build the adjacency list for the directed graph
        vector<vector<Edge>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2], e[3]});
        }

        // Dijkstra's algorithm to find the minimum arrival time
        // Priority queue stores {time, node}, using a min-heap
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(n, 2000000000); // Initialize with a value larger than any possible arrival time

        // Starting point: node 0 at time 0
        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [t, u] = pq.top();
            pq.pop();

            // If we already found a better way to reach this node, skip
            if (t > dist[u]) continue;
            
            // If we reached the destination, return the time
            if (u == n - 1) return t;

            for (const auto& edge : adj[u]) {
                // The earliest time we can start using this edge is max(current time, edge start window)
                int t_use = max(t, edge.start);
                
                // Check if the edge is still available at the time we want to use it
                if (t_use <= edge.end) {
                    int t_arrival = t_use + 1;
                    if (t_arrival < dist[edge.to]) {
                        dist[edge.to] = t_arrival;
                        pq.push({t_arrival, edge.to});
                    }
                }
            }
        }

        // If node n-1 is unreachable
        return -1;
    }
};
# @lc code=end