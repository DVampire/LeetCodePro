#include <bits/stdc++.h>
using namespace std;

/*
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#
*/

// @lc code=start
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        (void)threshold; // threshold >= 1, and we can always keep outdegree <= 1 by choosing a tree.

        vector<vector<pair<int,int>>> rev(n);
        int maxW = 0;
        for (auto &e : edges) {
            int a = e[0], b = e[1], w = e[2];
            rev[b].push_back({a, w});
            maxW = max(maxW, w);
        }

        auto feasible = [&](int X) -> bool {
            vector<char> vis(n, 0);
            queue<int> q;
            vis[0] = 1;
            q.push(0);
            int seen = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto &[v, w] : rev[u]) {
                    if (w <= X && !vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                        if (++seen == n) return true;
                    }
                }
            }
            return seen == n;
        };

        if (!feasible(maxW)) return -1;

        int lo = 0, hi = maxW, ans = maxW;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};
// @lc code=end
