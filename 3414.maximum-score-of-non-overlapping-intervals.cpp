#include <vector>
#include <algorithm>

using namespace std;

#
# @lc app=leetcode id=3414 lang=cpp
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
class Solution {
    struct Interval {
        int l, r, weight, id;
    };

    struct State {
        long long weight;
        vector<int> indices;

        State() : weight(-1) {}
        State(long long w, vector<int> idx) : weight(w), indices(idx) {}
    };

    bool isBetter(const State& a, const State& b) {
        if (a.weight != b.weight) return a.weight > b.weight;
        if (a.indices.empty()) return false;
        if (b.indices.empty()) return true;
        return a.indices < b.indices;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> sorted_intervals(n);
        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(sorted_intervals.begin(), sorted_intervals.end(), [](const Interval& a, const Interval& b) {
            if (a.r != b.r) return a.r < b.r;
            return a.l < b.l;
        });

        vector<int> end_times;
        for (const auto& inter : sorted_intervals) {
            end_times.push_back(inter.r);
        }

        vector<State> prev_dp(n + 1, State(0, {}));
        State final_ans(0, {});

        for (int k = 1; k <= 4; ++k) {
            vector<State> curr_dp(n + 1);
            for (int i = 1; i <= n; ++i) {
                // Case 1: Don't pick current interval
                curr_dp[i] = curr_dp[i - 1];

                // Case 2: Pick current interval
                int p = lower_bound(end_times.begin(), end_times.begin() + i - 1, sorted_intervals[i - 1].l) - end_times.begin();
                if (prev_dp[p].weight != -1) {
                    long long new_weight = prev_dp[p].weight + sorted_intervals[i - 1].weight;
                    vector<int> new_indices = prev_dp[p].indices;
                    new_indices.push_back(sorted_intervals[i - 1].id);
                    sort(new_indices.begin(), new_indices.end());
                    
                    State newState(new_weight, new_indices);
                    if (curr_dp[i].weight == -1 || isBetter(newState, curr_dp[i])) {
                        curr_dp[i] = newState;
                    }
                }
            }
            prev_dp = curr_dp;
            if (isBetter(prev_dp[n], final_ans)) {
                final_ans = prev_dp[n];
            }
        }

        return final_ans.indices;
    }
};
# @lc code=end