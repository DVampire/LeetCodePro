#
# @lc app=leetcode id=3646 lang=cpp
#
# [3646] Next Special Palindrome Number
#
# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long specialPalindrome(long long n) {
        static vector<long long> all;
        static bool inited = false;
        if (!inited) {
            inited = true;

            auto genForSubset = [&](const array<int,10>& cnt) {
                int len = 0;
                for (int d = 1; d <= 9; d++) len += cnt[d];
                if (len == 0 || len > 17) return;

                int odd = -1;
                for (int d = 1; d <= 9; d++) {
                    if (cnt[d] % 2 == 1) {
                        if (odd != -1) return; // more than one odd-count digit
                        odd = d;
                    }
                }
                if ((len % 2 == 0 && odd != -1) || (len % 2 == 1 && odd == -1)) return;

                int halfLen = len / 2;
                array<int,10> halfCnt{};
                for (int d = 1; d <= 9; d++) halfCnt[d] = cnt[d] / 2;

                string half(halfLen, '0');

                function<void(int)> dfs = [&](int pos) {
                    if (pos == halfLen) {
                        string s = half;
                        if (odd != -1) s.push_back(char('0' + odd));
                        string r = half;
                        reverse(r.begin(), r.end());
                        s += r;
                        all.push_back(stoll(s));
                        return;
                    }
                    for (int d = 1; d <= 9; d++) {
                        if (halfCnt[d] == 0) continue;
                        halfCnt[d]--;
                        half[pos] = char('0' + d);
                        dfs(pos + 1);
                        halfCnt[d]++;
                    }
                };

                dfs(0);
            };

            // enumerate all subsets of digits 1..9
            for (int mask = 1; mask < (1 << 9); mask++) {
                array<int,10> cnt{};
                int len = 0;
                for (int i = 0; i < 9; i++) {
                    if (mask & (1 << i)) {
                        int d = i + 1;
                        cnt[d] = d;
                        len += d;
                    }
                }
                if (len <= 17) genForSubset(cnt);
            }

            sort(all.begin(), all.end());
            all.erase(unique(all.begin(), all.end()), all.end());
        }

        auto it = upper_bound(all.begin(), all.end(), n);
        return *it; // guaranteed to exist for n <= 1e15
    }
};
# @lc code=end
