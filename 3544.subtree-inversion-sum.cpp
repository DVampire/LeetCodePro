#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3544 lang=cpp
//
// [3544] Subtree Inversion Sum
//

// @lc code=start
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = (int)nums.size();
        int m = 2 * (n - 1);

        // Build adjacency using arrays (memory efficient)
        vector<int> head(n, -1), to(m), nxt(m);
        int ei = 0;
        auto addEdge = [&](int u, int v) {
            to[ei] = v;
            nxt[ei] = head[u];
            head[u] = ei++;
        };
        for (auto &e : edges) {
            addEdge(e[0], e[1]);
            addEdge(e[1], e[0]);
        }

        // Root the tree at 0, get parent and order
        vector<int> parent(n, -1);
        vector<int> order;
        order.reserve(n);
        vector<int> st;
        st.reserve(n);
        st.push_back(0);
        parent[0] = -1;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (v == parent[u]) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }

        int stride = k + 1; // we will use distances d in [1..k], index 0 unused
        vector<long long> dp((long long)n * 2 * stride, 0);
        auto idx = [&](int u, int p, int d) -> long long {
            return ((long long)u * 2 + p) * stride + d;
        };

        // Postorder DP
        for (int it = n - 1; it >= 0; --it) {
            int u = order[it];

            // base sums for "not invert" option
            static long long base0[51], base1[51];
            for (int d = 1; d <= k; d++) base0[d] = base1[d] = 0;

            // sums for "invert" option (only used when d==k)
            long long invBase0 = 0; // when parent parity p=0, children get parity 1
            long long invBase1 = 0; // when parent parity p=1, children get parity 0

            // accumulate children contributions
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (v == parent[u]) continue;

                // For not invert: child distance is min(d+1,k)
                for (int d = 1; d <= k - 1; d++) {
                    base0[d] += dp[idx(v, 0, d + 1)];
                    base1[d] += dp[idx(v, 1, d + 1)];
                }
                base0[k] += dp[idx(v, 0, k)];
                base1[k] += dp[idx(v, 1, k)];

                // For invert at u: child parity toggles, distance becomes 1
                invBase0 += dp[idx(v, 1, 1)];
                invBase1 += dp[idx(v, 0, 1)];
            }

            // fill dp[u][p][d]
            for (int d = 1; d <= k; d++) {
                // p = 0: current sign is +
                dp[idx(u, 0, d)] = (long long)nums[u] + base0[d];
                // p = 1: current sign is -
                dp[idx(u, 1, d)] = -(long long)nums[u] + base1[d];
            }

            // invert allowed only when d == k
            {
                // if p=0 and invert: node contributes -nums[u], children use invBase0
                long long cand0 = -(long long)nums[u] + invBase0;
                dp[idx(u, 0, k)] = max(dp[idx(u, 0, k)], cand0);

                // if p=1 and invert: node contributes +nums[u], children use invBase1
                long long cand1 = (long long)nums[u] + invBase1;
                dp[idx(u, 1, k)] = max(dp[idx(u, 1, k)], cand1);
            }
        }

        // Root starts with parity 0 and no inverted ancestor within k-1 => d=k
        return dp[idx(0, 0, k)];
    }
};
// @lc code=end
