#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution {
public:
    long long popcountDepth(long long n, int k) {
        auto get_depth = [](long long x) -> int {
            int dep = 0;
            while (x != 1) {
                x = __builtin_popcountll(x);
                dep++;
            }
            return dep;
        };

        if (k == 0) return 1LL;

        std::vector<int> weights;
        for (int y = 1; y <= 64; ++y) {
            if (get_depth(y) == k - 1) {
                weights.push_back(y);
            }
        }

        auto count_up_to = [&](int target_w) -> long long {
            std::vector<int> digits(60);
            for (int i = 0; i < 60; ++i) {
                digits[i] = (n >> (59 - i)) & 1;
            }
            int max_used = target_w;
            std::vector<std::vector<std::vector<long long>>> dp(
                61, std::vector<std::vector<long long>>(max_used + 1, std::vector<long long>(2, 0LL)));
            for (int used = 0; used <= max_used; ++used) {
                dp[60][used][0] = (used == max_used ? 1LL : 0LL);
                dp[60][used][1] = (used == max_used ? 1LL : 0LL);
            }
            for (int pos = 59; pos >= 0; --pos) {
                for (int used = 0; used <= max_used; ++used) {
                    for (int tig = 0; tig < 2; ++tig) {
                        int up = tig ? digits[pos] : 1;
                        long long sum = 0;
                        for (int d = 0; d <= up; ++d) {
                            int nused = used + d;
                            if (nused > max_used) continue;
                            int ntig = (tig && (d == up)) ? 1 : 0;
                            sum += dp[pos + 1][nused][ntig];
                        }
                        dp[pos][used][tig] = sum;
                    }
                }
            }
            return dp[0][0][1];
        };

        long long ans = 0;
        for (int w : weights) {
            ans += count_up_to(w);
        }
        if (k == 1) {
            ans -= 1;
        }
        return ans;
    }
};
# @lc code=end