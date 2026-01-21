#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        vector<vector<bool>> can_reduce(n, vector<bool>(n, false));
        auto is_removable = [&](char a, char b) -> bool {
            int x = a - 'a', y = b - 'a';
            int d = abs(x - y);
            return d == 1 || d == 25;
        };
        // Base case: length 2
        for (int i = 0; i < n - 1; ++i) {
            if (is_removable(s[i], s[i + 1])) {
                can_reduce[i][i + 1] = true;
            }
        }
        // Interval DP for can_reduce
        for (int leng = 4; leng <= n; leng += 2) {
            for (int l = 0; l <= n - leng; ++l) {
                int r = l + leng - 1;
                // Wrapping
                bool inner_ok = (l + 1 > r - 1) || can_reduce[l + 1][r - 1];
                if (is_removable(s[l], s[r]) && inner_ok) {
                    can_reduce[l][r] = true;
                }
                // Splits
                if (!can_reduce[l][r]) {
                    for (int m = l; m < r; ++m) {
                        bool left_ok = can_reduce[l][m];
                        bool right_ok = (m + 1 <= r) && can_reduce[m + 1][r];
                        if (left_ok && right_ok) {
                            can_reduce[l][r] = true;
                            break;
                        }
                    }
                }
            }
        }
        // Now compute f[i]: lex smallest from s[i..n-1]
        vector<string> f(n + 1, "");
        f[n] = "";
        for (int i = n - 1; i >= 0; --i) {
            int suffix_len = n - i;
            bool can_empty = (suffix_len % 2 == 0) && can_reduce[i][n - 1];
            if (can_empty) {
                f[i] = "";
                continue;
            }
            // Min non-empty
            string best = string(1, s[i]) + f[i + 1];
            for (int j = i + 1; j < n; ++j) {
                int gap_l = i;
                int gap_r = j - 1;
                bool gap_ok = (gap_r < gap_l) || can_reduce[gap_l][gap_r];
                if (gap_ok) {
                    string cand = string(1, s[j]) + f[j + 1];
                    if (cand < best) {
                        best = cand;
                    }
                }
            }
            f[i] = best;
        }
        return f[0];
    }
};
# @lc code=end
