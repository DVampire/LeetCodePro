#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3604 lang=cpp
 *
 * [3604] Minimum Time to Reach Destination in Directed Graph
 */

// @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        struct Edge {
            int to;
            int s;
            int e;
        };

        vector<vector<Edge>> g(n);
        g.reserve(n);
        for (auto &ed : edges) {
            int u = ed[0], v = ed[1], s = ed[2], e = ed[3];
            g[u].push_back({v, s, e});
        }

        const long long INF = (1LL<<62);
        vector<long long> dist(n, INF);
        dist[0] = 0;

        using P = pair<long long,int>; // (time, node)
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [t, u] = pq.top();
            pq.pop();
            if (t != dist[u]) continue;
            if (u == n - 1) return (int)t;

            for (const auto &ed : g[u]) {
                long long depart = max<long long>(t, ed.s);
                if (depart > ed.e) continue; // cannot use this edge
                long long nt = depart + 1;
                if (nt < dist[ed.to]) {
                    dist[ed.to] = nt;
                    pq.push({nt, ed.to});
                }
            }
        }

        return -1;
    }
};
// @lc code=end
