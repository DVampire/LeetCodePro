#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3387 lang=cpp
//
// [3387] Maximize Amount After Two Days of Conversions
//

// @lc code=start
class Solution {
    using ld = long double;

    struct Edge {
        int u, v;
        ld w;
    };

    vector<ld> bellmanMax(int source, int V, const vector<Edge>& edges) {
        vector<ld> best(V, 0.0L);
        best[source] = 1.0L;

        for (int it = 0; it < V - 1; ++it) {
            bool changed = false;
            for (const auto& e : edges) {
                if (best[e.u] <= 0.0L) continue;
                ld cand = best[e.u] * e.w;
                if (cand > best[e.v] + 1e-18L) {
                    best[e.v] = cand;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        return best;
    }

public:
    double maxAmount(string initialCurrency,
                     vector<vector<string>>& pairs1, vector<double>& rates1,
                     vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string,int> id;
        id.reserve(64);
        auto getId = [&](const string& s) -> int {
            auto it = id.find(s);
            if (it != id.end()) return it->second;
            int nid = (int)id.size();
            id.emplace(s, nid);
            return nid;
        };

        int init = getId(initialCurrency);
        for (auto &p : pairs1) { getId(p[0]); getId(p[1]); }
        for (auto &p : pairs2) { getId(p[0]); getId(p[1]); }
        int V = (int)id.size();

        vector<Edge> edges1, edges2;
        edges1.reserve(pairs1.size() * 2);
        edges2.reserve(pairs2.size() * 2);

        for (int i = 0; i < (int)pairs1.size(); ++i) {
            int a = getId(pairs1[i][0]);
            int b = getId(pairs1[i][1]);
            ld r = (ld)rates1[i];
            edges1.push_back({a, b, r});
            edges1.push_back({b, a, 1.0L / r});
        }
        for (int i = 0; i < (int)pairs2.size(); ++i) {
            int a = getId(pairs2[i][0]);
            int b = getId(pairs2[i][1]);
            ld r = (ld)rates2[i];
            edges2.push_back({a, b, r});
            edges2.push_back({b, a, 1.0L / r});
        }

        vector<ld> bestDay1 = bellmanMax(init, V, edges1);

        ld ans = 1.0L; // do nothing both days
        for (int x = 0; x < V; ++x) {
            if (bestDay1[x] <= 0.0L) continue;
            vector<ld> bestDay2FromX = bellmanMax(x, V, edges2);
            if (bestDay2FromX[init] <= 0.0L) continue;
            ans = max(ans, bestDay1[x] * bestDay2FromX[init]);
        }

        return (double)ans;
    }
};
// @lc code=end
