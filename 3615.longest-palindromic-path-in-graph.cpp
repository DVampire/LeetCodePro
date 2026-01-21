#
# @lc app=leetcode id=3615 lang=cpp
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // neighCharMask[u][c] = bitmask of neighbors of u with label == ('a'+c)
        vector<array<int, 26>> neighCharMask(n);
        for (int i = 0; i < n; i++) neighCharMask[i].fill(0);
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                neighCharMask[u][label[v] - 'a'] |= (1 << v);
            }
        }

        int N = 1 << n;
        // dp[mask][u] is a bitmask of possible right endpoints v
        vector<vector<int>> dp(N, vector<int>(n, 0));
        deque<tuple<int,int,int>> q;

        auto pushState = [&](int mask, int u, int v) {
            if ((dp[mask][u] >> v) & 1) return;
            dp[mask][u] |= (1 << v);
            q.emplace_back(mask, u, v);
        };

        int ans = 1;

        // length 1 palindromes (single node center)
        for (int i = 0; i < n; i++) {
            pushState(1 << i, i, i);
        }

        // length 2 palindromes (edge with equal labels)
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            if (label[u] == label[v]) {
                int mask = (1 << u) | (1 << v);
                pushState(mask, u, v);
                pushState(mask, v, u);
                ans = max(ans, 2);
            }
        }

        while (!q.empty()) {
            auto [mask, u, v] = q.front();
            q.pop_front();

            ans = max(ans, __builtin_popcount((unsigned)mask));

            int usedMask = mask;
            for (int c = 0; c < 26; c++) {
                int left = neighCharMask[u][c] & ~usedMask;
                int right = neighCharMask[v][c] & ~usedMask;
                if (!left || !right) continue;

                // iterate a in left
                for (int lx = left; lx; lx &= (lx - 1)) {
                    int a = __builtin_ctz((unsigned)lx);
                    int right2 = right & ~(1 << a); // ensure a != b
                    for (int rx = right2; rx; rx &= (rx - 1)) {
                        int b = __builtin_ctz((unsigned)rx);
                        int newMask = usedMask | (1 << a) | (1 << b);
                        pushState(newMask, a, b);
                        pushState(newMask, b, a);
                    }
                }
            }
        }

        return ans;
    }
};
# @lc code=end
