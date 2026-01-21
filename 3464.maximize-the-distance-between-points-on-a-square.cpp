#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3464 lang=cpp
 *
 * [3464] Maximize the Distance Between Points on a Square
 */

// @lc code=start
class Solution {
    struct Pt {
        long long u;   // x + y
        long long f;   // |x - y| == |v|
        int chain;     // 0: v>=0, 1: v<0
    };

    struct State {
        long long uU, uL; // last chosen u on upper/lower chain; -1 means none
        long long fU, fL; // corresponding |v|
    };

    static void prune(vector<State>& vec) {
        if (vec.size() <= 1) return;
        sort(vec.begin(), vec.end(), [](const State& a, const State& b) {
            if (a.uU != b.uU) return a.uU < b.uU;
            return a.uL < b.uL;
        });

        // Remove dominated states:
        // A dominates B if A.uU <= B.uU and A.uL <= B.uL.
        // After sorting by uU ascending, we keep strictly decreasing uL.
        vector<State> res;
        res.reserve(vec.size());
        long long bestL = LLONG_MAX;
        for (const auto& s : vec) {
            if (s.uL < bestL) {
                res.push_back(s);
                bestL = s.uL;
            }
        }
        vec.swap(res);
    }

    static inline bool canAddUpper(const State& st, const Pt& p, long long d) {
        if (st.uU != -1 && p.u - st.uU < d) return false;
        if (st.uL != -1) {
            long long du = p.u - st.uL;
            if (du < d && p.f + st.fL < d) return false;
        }
        return true;
    }

    static inline bool canAddLower(const State& st, const Pt& p, long long d) {
        if (st.uL != -1 && p.u - st.uL < d) return false;
        if (st.uU != -1) {
            long long du = p.u - st.uU;
            if (du < d && p.f + st.fU < d) return false;
        }
        return true;
    }

    static bool feasible(long long d, const vector<Pt>& pts, int k) {
        // dp[t] = Pareto frontier of states after selecting exactly t points.
        vector<vector<State>> dp(k + 1);
        dp[0].push_back(State{-1, -1, (long long)4e18, (long long)4e18});

        for (const auto& p : pts) {
            for (int t = k - 1; t >= 0; --t) {
                if (dp[t].empty()) continue;
                auto& cur = dp[t];
                auto& nxt = dp[t + 1];

                if (p.chain == 0) {
                    for (const auto& st : cur) {
                        if (!canAddUpper(st, p, d)) continue;
                        nxt.push_back(State{p.u, st.uL, p.f, st.fL});
                    }
                } else {
                    for (const auto& st : cur) {
                        if (!canAddLower(st, p, d)) continue;
                        nxt.push_back(State{st.uU, p.u, st.fU, p.f});
                    }
                }
            }

            // Prune all layers (k is small).
            for (int t = 1; t <= k; ++t) prune(dp[t]);
            if (!dp[k].empty()) return true;
        }
        return !dp[k].empty();
    }

public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        long long S = (long long)side;
        vector<Pt> pts;
        pts.reserve(points.size());

        for (auto &p : points) {
            long long x = p[0], y = p[1];
            long long u = x + y;
            long long v = x - y;
            int chain = (v >= 0) ? 0 : 1;
            long long f = llabs(v);
            pts.push_back(Pt{u, f, chain});
        }

        sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
            if (a.u != b.u) return a.u < b.u;
            return a.chain < b.chain;
        });

        long long lo = 0, hi = 2 * S + 1; // [lo, hi)
        while (lo + 1 < hi) {
            long long mid = (lo + hi) / 2;
            if (feasible(mid, pts, k)) lo = mid;
            else hi = mid;
        }
        return (int)lo;
    }
};
// @lc code=end
