#
# @lc app=leetcode id=3609 lang=cpp
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    int minMoves(int sx_, int sy_, int tx_, int ty_) {
        ll sx = sx_, sy = sy_, tx = tx_, ty = ty_;
        if (sx == tx && sy == ty) return 0;

        auto get_prev = [](ll x, ll y) -> vector<pair<ll, ll>> {
            vector<pair<ll, ll>> res;
            // Undo x-move
            if (x % 2 == 0 && x / 2 >= y) {
                res.emplace_back(x / 2, y);
            }
            if (x >= y && x < 2 * y) {
                res.emplace_back(x - y, y);
            }
            // Undo y-move
            if (y % 2 == 0 && y / 2 >= x) {
                res.emplace_back(x, y / 2);
            }
            if (y >= x && y < 2 * x) {
                res.emplace_back(x, y - x);
            }
            return res;
        };

        queue<pair<ll, ll>> q;
        map<pair<ll, ll>, int> dist;
        q.emplace(tx, ty);
        dist[{tx, ty}] = 0;

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            int d = dist[{x, y}];
            auto pres = get_prev(x, y);
            for (auto [nx, ny] : pres) {
                if (nx < 0 || ny < 0) continue;
                pair<ll, ll> np = {nx, ny};
                if (dist.count(np)) continue;
                dist[np] = d + 1;
                q.emplace(nx, ny);
                if (nx == sx && ny == sy) {
                    return d + 1;
                }
            }
        }
        return -1;
    }
};
# @lc code=end