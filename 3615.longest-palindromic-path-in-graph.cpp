#
# @lc app=leetcode id=3615 lang=cpp
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int maxmask = 1 << n;
        int statesize = n * n * maxmask;
        vector<char> vis(statesize, 0);
        auto idx = [&](int l, int r, int m) -> int {
            return (l * n + r) * maxmask + m;
        };
        queue<tuple<int, int, int>> q;
        int ans = 1;
        // Odd bases: single nodes
        for (int u = 0; u < n; ++u) {
            int msk = 1 << u;
            int id = idx(u, u, msk);
            if (!vis[id]) {
                vis[id] = 1;
                q.push({u, u, msk});
            }
        }
        // Even bases: adjacent pairs with same label
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                if (v > u && label[u] == label[v]) {
                    int msk = (1 << u) | (1 << v);
                    int id1 = idx(u, v, msk);
                    if (!vis[id1]) {
                        vis[id1] = 1;
                        q.push({u, v, msk});
                        ans = 2;
                    }
                    int id2 = idx(v, u, msk);
                    if (!vis[id2]) {
                        vis[id2] = 1;
                        q.push({v, u, msk});
                        ans = 2;
                    }
                }
            }
        }
        while (!q.empty()) {
            auto [l, r, msk] = q.front(); q.pop();
            ans = max(ans, __builtin_popcount(msk));
            for (int x : adj[l]) {
                if ((msk & (1 << x)) == 0) {
                    char ch = label[x];
                    for (int y : adj[r]) {
                        if ((msk & (1 << y)) == 0 && x != y && label[y] == ch) {
                            int nmsk = msk | (1 << x) | (1 << y);
                            int nid = idx(x, y, nmsk);
                            if (!vis[nid]) {
                                vis[nid] = 1;
                                q.push({x, y, nmsk});
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};
# @lc code=end