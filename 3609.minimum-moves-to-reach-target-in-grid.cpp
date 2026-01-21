#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3609 lang=cpp
 *
 * [3609] Minimum Moves to Reach Target in Grid
 */

// @lc code=start
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        using ll = long long;
        const ll INF = (1LL<<60);

        auto keyOf = [&](ll x, ll y) -> uint64_t {
            return (uint64_t(x) << 32) | uint32_t(y);
        };

        unordered_map<uint64_t, ll> memo;
        memo.reserve(1 << 16);

        function<ll(ll,ll)> dfs = [&](ll x, ll y) -> ll {
            if (x < sx || y < sy) return INF;
            if (x == sx && y == sy) return 0;
            if (x == 0 && y == 0) return INF; // cannot come from elsewhere unless start is (0,0) (handled above)

            uint64_t key = keyOf(x, y);
            auto it = memo.find(key);
            if (it != memo.end()) return it->second;

            ll ans = INF;

            if (x == y) {
                // x == y == k > 0
                ans = min(ans, 1 + dfs(x, 0));
                ans = min(ans, 1 + dfs(0, y));
            } else if (x > y) {
                // Predecessor by halving x (reverse of doubling x)
                if ((x % 2LL) == 0) {
                    ll px = x / 2;
                    if (px >= y) ans = min(ans, 1 + dfs(px, y));
                }
                // Predecessor by subtracting y (reverse of adding y to x)
                if (2LL * y > x) {
                    ans = min(ans, 1 + dfs(x - y, y));
                }
            } else { // y > x
                if ((y % 2LL) == 0) {
                    ll py = y / 2;
                    if (py >= x) ans = min(ans, 1 + dfs(x, py));
                }
                if (2LL * x > y) {
                    ans = min(ans, 1 + dfs(x, y - x));
                }
            }

            memo[key] = ans;
            return ans;
        };

        ll res = dfs(tx, ty);
        return (res >= INF/2) ? -1 : (int)res;
    }
};
// @lc code=end
