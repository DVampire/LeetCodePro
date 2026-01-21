#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = (int)s.size();
        auto consecutive = [&](char a, char b) -> bool {
            int x = a - 'a', y = b - 'a';
            return (x + 1) % 26 == y || (y + 1) % 26 == x;
        };

        vector<vector<char>> rem(n, vector<char>(n, 0));
        auto canRemove = [&](int l, int r) -> bool {
            if (l > r) return true;
            return rem[l][r];
        };

        for (int len = 2; len <= n; ++len) {
            if (len % 2 == 1) continue; // odd length can't be fully removed
            for (int l = 0; l + len - 1 < n; ++l) {
                int r = l + len - 1;
                for (int k = l + 1; k <= r; k += 2) { // k-l must be odd
                    if (consecutive(s[l], s[k]) && canRemove(l + 1, k - 1) && canRemove(k + 1, r)) {
                        rem[l][r] = 1;
                        break;
                    }
                }
            }
        }

        // memo[state], where state = lastKeptIndex + 1 (so 0 means lastKeptIndex = -1)
        vector<string> memo(n + 1);
        vector<char> vis(n + 1, 0);

        function<string(int)> dfs = [&](int state) -> string {
            if (vis[state]) return memo[state];
            vis[state] = 1;
            int last = state - 1;

            bool hasBest = false;
            string best;

            for (int nxt = last + 1; nxt <= n; ++nxt) {
                // Need to be able to remove the gap (last+1 .. nxt-1)
                if (!canRemove(last + 1, nxt - 1)) continue;

                string cand;
                if (nxt == n) {
                    cand = ""; // end, suffix removable by condition above
                } else {
                    cand.reserve(1 + (n - nxt));
                    cand.push_back(s[nxt]);
                    string tail = dfs(nxt + 1);
                    cand += tail;
                }

                if (!hasBest || cand < best) {
                    best = std::move(cand);
                    hasBest = true;
                }
            }

            memo[state] = hasBest ? best : string();
            return memo[state];
        };

        return dfs(0);
    }
};
// @lc code=end
