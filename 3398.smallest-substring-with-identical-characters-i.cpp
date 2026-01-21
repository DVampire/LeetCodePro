#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();
        auto can = [&](int K) -> bool {
            const int INF = 2000000000;
            std::vector<std::vector<int>> prev_layer(K + 1, std::vector<int>(2, INF));
            // First character
            for (int c = 0; c < 2; ++c) {
                int cost = ((s[0] - '0') != c ? 1 : 0);
                prev_layer[1][c] = cost;
            }
            for (int i = 1; i < n; ++i) {
                std::vector<std::vector<int>> curr_layer(K + 1, std::vector<int>(2, INF));
                for (int p_len = 1; p_len <= K; ++p_len) {
                    for (int p_c = 0; p_c < 2; ++p_c) {
                        if (prev_layer[p_len][p_c] == INF) continue;
                        for (int new_c = 0; new_c < 2; ++new_c) {
                            int cost = ((s[i] - '0') != new_c ? 1 : 0);
                            int new_len = (new_c == p_c ? p_len + 1 : 1);
                            if (new_len > K) continue;
                            curr_layer[new_len][new_c] = std::min(curr_layer[new_len][new_c],
                                prev_layer[p_len][p_c] + cost);
                        }
                    }
                }
                prev_layer = std::move(curr_layer);
            }
            int min_flips = INF;
            for (int len = 1; len <= K; ++len) {
                for (int c = 0; c < 2; ++c) {
                    min_flips = std::min(min_flips, prev_layer[len][c]);
                }
            }
            return min_flips <= numOps;
        };
        int left = 1, right = n, ans = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (can(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
# @lc code=end