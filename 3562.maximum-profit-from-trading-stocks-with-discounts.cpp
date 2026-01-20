#
# @lc app=leetcode id=3562 lang=cpp
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    int g[161][2][161];
    vector<int> adj[161];
    int B;

    void dfs(int u, const vector<int>& present, const vector<vector<int>>& adj, int budget, int g[161][2][161], const vector<int>& future) {
        // dp_buys[b] is the max profit from children when u buys its stock
        vector<int> dp_buys(budget + 1, 0);
        // dp_not_buys[b] is the max profit from children when u does not buy its stock
        vector<int> dp_not_buys(budget + 1, 0);

        for (int v : adj[u]) {
            dfs(v, present, adj, budget, g, future);
            
            // Knapsack merge for dp_buys with g[v][1]
            vector<int> next_buys(budget + 1, 0);
            for (int b = 0; b <= budget; ++b) {
                for (int kb = 0; kb <= b; ++kb) {
                    next_buys[b] = max(next_buys[b], dp_buys[b - kb] + g[v][1][kb]);
                }
            }
            dp_buys = next_buys;

            // Knapsack merge for dp_not_buys with g[v][0]
            vector<int> next_not_buys(budget + 1, 0);
            for (int b = 0; b <= budget; ++b) {
                for (int kb = 0; kb <= b; ++kb) {
                    next_not_buys[b] = max(next_not_buys[b], dp_not_buys[b - kb] + g[v][0][kb]);
                }
            }
            dp_not_buys = next_not_buys;
        }

        for (int b = 0; b <= budget; ++b) {
            // Case 0: u's boss did NOT buy. u can either not buy or buy at full price.
            g[u][0][b] = dp_not_buys[b];
            if (b >= present[u - 1]) {
                g[u][0][b] = max(g[u][0][b], (future[u - 1] - present[u - 1]) + dp_buys[b - present[u - 1]]);
            }

            // Case 1: u's boss DID buy. u can either not buy or buy at discounted price.
            g[u][1][b] = dp_not_buys[b];
            int disc_price = present[u - 1] / 2;
            if (b >= disc_price) {
                g[u][1][b] = max(g[u][1][b], (future[u - 1] - disc_price) + dp_buys[b - disc_price]);
            }
        }
    }

public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> local_adj(n + 1);
        for (const auto& edge : hierarchy) {
            local_adj[edge[0]].push_back(edge[1]);
        }

        int local_g[161][2][161];
        memset(local_g, 0, sizeof(local_g));

        dfs(1, present, local_adj, budget, local_g, future);

        return local_g[1][0][budget];
    }
};
# @lc code=end