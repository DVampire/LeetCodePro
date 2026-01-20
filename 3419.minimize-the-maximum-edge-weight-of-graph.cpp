#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3419 lang=cpp
//
// [3419] Minimize the Maximum Edge Weight of Graph
//

// @lc code=start
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        (void)threshold; // threshold >= 1; not additionally constraining as discussed.

        vector<vector<pair<int,int>>> rev(n);
        rev.reserve(n);
        for (auto &e : edges) {
            int a = e[0], b = e[1], w = e[2];
            rev[b].push_back({a, w}); // reverse edge
        }

        const int INF = 1e9 + 7;
        vector<int> dist(n, INF);
        dist[0] = 0;

        using P = pair<int,int>; // (dist, node)
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;

            for (auto &[v, w] : rev[u]) {
                int nd = max(d, w);
                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.push({nd, v});
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] >= INF) return -1;
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};
// @lc code=end
