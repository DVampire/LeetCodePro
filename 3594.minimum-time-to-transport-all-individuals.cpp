#
# @lc app=leetcode id=3594 lang=cpp
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        int N = 1 << n;
        vector<double> max_t(N, 0.0);
        for (int mask = 0; mask < N; ++mask) {
            double mx = 0.0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    mx = max(mx, (double)time[i]);
                }
            }
            max_t[mask] = mx;
        }
        int STATES = N * m;
        vector<double> dist(STATES, 1e100);
        auto encode = [&](int ml, int stg) -> int {
            return ml * m + stg;
        };
        int start_ml = (1 << n) - 1;
        int start_st = encode(start_ml, 0);
        dist[start_st] = 0.0;
        using T = pair<double, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0.0, start_st});
        double min_time = 1e100;
        while (!pq.empty()) {
            auto [cost, ust] = pq.top(); pq.pop();
            if (cost > dist[ust]) continue;
            int ml = ust / m;
            int s = ust % m;
            if (ml == 0) continue;
            for (int sub = ml; sub > 0; sub = (sub - 1) & ml) {
                int psz = __builtin_popcount(sub);
                if (psz > k) continue;
                double mt = max_t[sub];
                double d = mt * mul[s];
                int delta = (int)floor(d) % m;
                int ns = (s + delta) % m;
                int nml = ml ^ sub;
                if (nml == 0) {
                    min_time = min(min_time, cost + d);
                    continue;
                }
                for (int r = 0; r < n; ++r) {
                    if ((nml & (1 << r)) == 0) {  // r on right
                        double rdur = (double)time[r] * mul[ns];
                        int rdel = (int)floor(rdur) % m;
                        int fs = (ns + rdel) % m;
                        int fml = nml | (1 << r);
                        int v = encode(fml, fs);
                        double ncost = cost + d + rdur;
                        if (ncost < dist[v]) {
                            dist[v] = ncost;
                            pq.push({ncost, v});
                        }
                    }
                }
            }
        }
        if (min_time > 1e99) return -1.0;
        return min_time;
    }
};
# @lc code=end