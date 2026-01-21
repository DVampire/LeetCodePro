#
# @lc app=leetcode id=3367 lang=cpp
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        function<pair<long long, long long>(int, int)> dfs = [&](int u, int p) -> pair<long long, long long> {
            vector<long long> gains;
            long long total_full = 0;
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                auto [fmax, cmax] = dfs(v, u);
                total_full += fmax;
                long long gain = (long long)w + cmax - fmax;
                gains.push_back(gain);
            }
            sort(gains.rbegin(), gains.rend());
            long long cur = 0;
            long long maxf = 0;
            long long maxc = 0;
            int limf = min((int)gains.size(), k);
            int limc = min((int)gains.size(), k - 1);
            for (int j = 1; j <= (int)gains.size(); ++j) {
                cur += gains[j - 1];
                if (j <= limf) maxf = max(maxf, cur);
                if (j <= limc) maxc = max(maxc, cur);
            }
            long long full_u = total_full + maxf;
            long long cons_u = total_full + maxc;
            return {full_u, cons_u};
        };
        auto [ans, _] = dfs(0, -1);
        return ans;
    }
};
# @lc code=end