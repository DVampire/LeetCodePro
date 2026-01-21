#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> children(n);
        for (auto &e : hierarchy) {
            int u = e[0] - 1, v = e[1] - 1;
            children[u].push_back(v);
        }

        const long long NEG = -(1LL<<60);

        // dp0[u], dp1[u]
        vector<vector<long long>> dp0(n, vector<long long>(budget + 1, NEG));
        vector<vector<long long>> dp1(n, vector<long long>(budget + 1, NEG));

        // postorder traversal
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};
        vector<int> it(n, 0);
        vector<int> parent(n, -1);
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)children[u].size()) {
                int v = children[u][it[u]++];
                parent[v] = u;
                st.push_back(v);
            } else {
                order.push_back(u);
                st.pop_back();
            }
        }

        auto mergeKnapsack = [&](const vector<long long>& A, const vector<long long>& B) {
            vector<long long> C(budget + 1, NEG);
            for (int i = 0; i <= budget; i++) if (A[i] != NEG) {
                for (int j = 0; j + i <= budget; j++) if (B[j] != NEG) {
                    C[i + j] = max(C[i + j], A[i] + B[j]);
                }
            }
            return C;
        };

        for (int u : order) {
            // Combine children assuming u not bought (children parentBought = false)
            vector<long long> comb0(budget + 1, NEG);
            comb0[0] = 0;
            for (int v : children[u]) {
                comb0 = mergeKnapsack(comb0, dp0[v]);
            }

            // Combine children assuming u bought (children parentBought = true)
            vector<long long> comb1(budget + 1, NEG);
            comb1[0] = 0;
            for (int v : children[u]) {
                comb1 = mergeKnapsack(comb1, dp1[v]);
            }

            // dp0[u]: parent not bought => u cost is full
            // Option not buy: comb0
            dp0[u] = comb0;
            // Option buy: pay full cost
            {
                int cost = present[u];
                long long prof = (long long)future[u] - cost;
                if (cost <= budget) {
                    for (int b = 0; b + cost <= budget; b++) if (comb1[b] != NEG) {
                        dp0[u][b + cost] = max(dp0[u][b + cost], comb1[b] + prof);
                    }
                }
            }

            // dp1[u]: parent bought => u cost is discounted
            dp1[u] = comb0;
            {
                int cost = present[u] / 2;
                long long prof = (long long)future[u] - cost;
                if (cost <= budget) {
                    for (int b = 0; b + cost <= budget; b++) if (comb1[b] != NEG) {
                        dp1[u][b + cost] = max(dp1[u][b + cost], comb1[b] + prof);
                    }
                }
            }
        }

        long long ans = 0;
        for (int b = 0; b <= budget; b++) ans = max(ans, dp0[0][b]);
        return (int)ans;
    }
};
// @lc code=end
