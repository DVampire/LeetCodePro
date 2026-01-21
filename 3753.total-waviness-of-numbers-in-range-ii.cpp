#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        struct Res {
            long long cnt, sumw;
            Res(long long c = -1LL, long long s = 0LL) : cnt(c), sumw(s) {}
        };

        auto solve = [&](auto&& self, long long n) -> long long {
            if (n <= 0) return 0LL;
            string S = to_string(n);
            int L = S.length();
            const int MAX_POS = 17;
            const int MAX_PV = 11;
            int total_states = MAX_POS * 2 * 2 * MAX_PV * MAX_PV;
            vector<Res> memo(total_states);

            auto get_idx = [&](int pos, int tig, int lea, int p1, int p2) -> int {
                return (((pos * 2 + tig) * 2 + lea) * MAX_PV + (p1 + 1)) * MAX_PV + (p2 + 1);
            };

            function<Res(int, int, int, int, int)> dfs = [&](int pos, int tight, int lead, int prev1, int prev2) -> Res {
                if (pos == L) {
                    return Res(1LL, 0LL);
                }
                int idx = get_idx(pos, tight, lead, prev1, prev2);
                if (memo[idx].cnt != -1LL) {
                    return memo[idx];
                }
                Res ans(0LL, 0LL);
                int up = tight ? (S[pos] - '0') : 9;
                for (int d = 0; d <= up; ++d) {
                    int ntight = tight && (d == up);
                    int nlead = lead && (d == 0);
                    int np1 = -1;
                    int np2 = -1;
                    long long contrib = 0LL;
                    if (!nlead) {
                        int op1 = prev1;
                        int op2 = prev2;
                        np1 = d;
                        np2 = op1;
                        if (op2 != -1) {
                            int mid = op1;
                            if ((mid > op2 && mid > d) || (mid < op2 && mid < d)) {
                                contrib = 1LL;
                            }
                        }
                    }
                    Res sub = dfs(pos + 1, ntight, nlead, np1, np2);
                    ans.cnt += sub.cnt;
                    ans.sumw += sub.sumw + contrib * sub.cnt;
                }
                memo[idx] = ans;
                return ans;
            };

            return dfs(0, 1, 1, -1, -1).sumw;
        };

        return solve(solve, num2) - solve(solve, num1 - 1);
    }
};
# @lc code=end