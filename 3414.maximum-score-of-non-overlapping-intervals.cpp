#
# @lc app=leetcode id=3414 lang=cpp
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct State {
        long long score;
        int len;
        int idx[4];
    };

    static constexpr long long NEG = -(1LL<<60);

    static State invalidState() {
        State s;
        s.score = NEG;
        s.len = 0;
        for (int i = 0; i < 4; i++) s.idx[i] = 0;
        return s;
    }

    static bool lexLess(const State& a, const State& b) {
        int m = min(a.len, b.len);
        for (int i = 0; i < m; i++) {
            if (a.idx[i] != b.idx[i]) return a.idx[i] < b.idx[i];
        }
        return a.len < b.len; // shorter (prefix) is lexicographically smaller
    }

    static State better(const State& a, const State& b) {
        if (a.score == NEG) return b;
        if (b.score == NEG) return a;
        if (a.score != b.score) return (a.score > b.score) ? a : b;
        return lexLess(a, b) ? a : b;
    }

    static State addInterval(const State& base, int originalIdx, long long w) {
        if (base.score == NEG) return invalidState();
        State res = base;
        res.score += w;
        // insert originalIdx into res.idx keeping sorted
        int pos = res.len;
        while (pos > 0 && res.idx[pos - 1] > originalIdx) {
            res.idx[pos] = res.idx[pos - 1];
            pos--;
        }
        res.idx[pos] = originalIdx;
        res.len++;
        return res;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = (int)intervals.size();
        struct Item { long long l, r, w; int idx; };
        vector<Item> a;
        a.reserve(n);
        for (int i = 0; i < n; i++) {
            a.push_back({(long long)intervals[i][0], (long long)intervals[i][1], (long long)intervals[i][2], i});
        }
        sort(a.begin(), a.end(), [](const Item& x, const Item& y) {
            if (x.r != y.r) return x.r < y.r;
            if (x.l != y.l) return x.l < y.l;
            return x.idx < y.idx;
        });

        // 1-based for convenience
        vector<long long> ends(n + 1, LLONG_MIN);
        vector<Item> items(n + 1);
        for (int i = 1; i <= n; i++) {
            items[i] = a[i - 1];
            ends[i] = items[i].r;
        }

        // dp[i][j]: best using first i intervals (sorted by r), choosing exactly j
        vector<array<State, 5>> dp(n + 1);
        for (int j = 0; j <= 4; j++) dp[0][j] = invalidState();
        dp[0][0].score = 0;
        dp[0][0].len = 0;

        for (int i = 1; i <= n; i++) {
            // find p(i): last index < i with end < l_i
            long long target = items[i].l - 1; // end <= l-1
            int p = (int)(upper_bound(ends.begin() + 1, ends.begin() + i, target) - ends.begin()) - 1;

            for (int j = 0; j <= 4; j++) {
                State bestSkip = dp[i - 1][j];
                State bestTake = invalidState();
                if (j > 0) {
                    bestTake = addInterval(dp[p][j - 1], items[i].idx, items[i].w);
                }
                dp[i][j] = better(bestSkip, bestTake);
            }
        }

        State ans = invalidState();
        for (int j = 0; j <= 4; j++) ans = better(ans, dp[n][j]);

        vector<int> res;
        res.reserve(ans.len);
        for (int i = 0; i < ans.len; i++) res.push_back(ans.idx[i]);
        return res;
    }
};
# @lc code=end
