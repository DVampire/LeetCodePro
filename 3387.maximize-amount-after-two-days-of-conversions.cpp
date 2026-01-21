#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        set<string> curr_set;
        curr_set.insert(initialCurrency);
        for (auto& p : pairs1) {
            curr_set.insert(p[0]);
            curr_set.insert(p[1]);
        }
        for (auto& p : pairs2) {
            curr_set.insert(p[0]);
            curr_set.insert(p[1]);
        }
        vector<string> currencies(curr_set.begin(), curr_set.end());
        int C = currencies.size();
        unordered_map<string, int> id;
        for (int i = 0; i < C; ++i) {
            id[currencies[i]] = i;
        }
        int S = id[initialCurrency];

        // Build g1
        vector<vector<pair<int, double>>> g1(C);
        int n1 = pairs1.size();
        for (int i = 0; i < n1; ++i) {
            int u = id[pairs1[i][0]];
            int v = id[pairs1[i][1]];
            double r = rates1[i];
            g1[u].emplace_back(v, r);
            g1[v].emplace_back(u, 1.0 / r);
        }

        // Build g2
        vector<vector<pair<int, double>>> g2(C);
        int n2 = pairs2.size();
        for (int i = 0; i < n2; ++i) {
            int u = id[pairs2[i][0]];
            int v = id[pairs2[i][1]];
            double r = rates2[i];
            g2[u].emplace_back(v, r);
            g2[v].emplace_back(u, 1.0 / r);
        }

        auto max_from = [&](int src, const vector<vector<pair<int, double>>>& g) -> vector<double> {
            vector<double> dist(C, 0.0);
            dist[src] = 1.0;
            for (int iter = 0; iter < C; ++iter) {
                bool updated = false;
                for (int u = 0; u < C; ++u) {
                    if (dist[u] <= 0.0) continue;
                    for (auto& p : g[u]) {
                        int v = p.first;
                        double cand = dist[u] * p.second;
                        if (cand > dist[v] + 1e-10) {
                            dist[v] = cand;
                            updated = true;
                        }
                    }
                }
                if (!updated) break;
            }
            return dist;
        };

        vector<double> day1 = max_from(S, g1);

        vector<double> day2_to_s(C, 0.0);
        for (int x = 0; x < C; ++x) {
            vector<double> temp = max_from(x, g2);
            day2_to_s[x] = temp[S];
        }

        double ans = 0.0;
        for (int x = 0; x < C; ++x) {
            double total = day1[x] * day2_to_s[x];
            if (total > ans) ans = total;
        }
        return ans;
    }
};
# @lc code=end