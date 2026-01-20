#
# @lc app=leetcode id=3538 lang=cpp
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        // dp[i][p][r] = min travel time to reach sign i, where p was the sign kept before i,
        // and r signs have been removed so far.
        const int INF = 1e9;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, INF)));

        // Precompute prefix sums for travel times to calculate sums in O(1)
        vector<int> prefix_time(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_time[i + 1] = prefix_time[i] + time[i];
        }

        auto get_sum = [&](int start, int end) {
            if (start > end) return 0;
            return prefix_time[end + 1] - prefix_time[start];
        };

        // Base case: first segment starting from position[0]
        for (int j1 = 1; j1 < n; ++j1) {
            int removed = j1 - 1;
            if (removed <= k) {
                dp[j1][0][removed] = (position[j1] - position[0]) * time[0];
            }
        }

        // DP transitions
        for (int r = 0; r <= k; ++r) {
            for (int i = 1; i < n - 1; ++i) { // currently at sign i
                for (int p = 0; p < i; ++p) { // sign kept before i was p
                    if (dp[i][p][r] == INF) continue;

                    for (int next = i + 1; next < n; ++next) {
                        int next_r = r + (next - i - 1);
                        if (next_r <= k) {
                            int speed = time[i] + get_sum(p + 1, i - 1);
                            int travel_cost = (position[next] - position[i]) * speed;
                            if (dp[i][p][r] + travel_cost < dp[next][i][next_r]) {
                                dp[next][i][next_r] = dp[i][p][r] + travel_cost;
                            }
                        }
                    }
                }
            }
        }

        int ans = INF;
        for (int p = 0; p < n - 1; ++p) {
            ans = min(ans, dp[n - 1][p][k]);
        }

        return ans;
    }
};
# @lc code=end