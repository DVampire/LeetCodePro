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
        string T = to_string(n);
        int dd = T.size();
        string best = "";

        for (int mask = 1; mask < (1 << 9); ++mask) {
            vector<int> counts(10, 0);
            int LL = 0;
            for (int i = 0; i < 9; ++i) {
                if (mask & (1 << i)) {
                    int dig = i + 1;
                    counts[dig] = dig;
                    LL += dig;
                }
            }
            if (LL < dd) continue;

            // check odds
            int odd_cnt = 0, odd_dig = -1;
            for (int dig = 1; dig <= 9; ++dig) {
                if (counts[dig] % 2 == 1) {
                    ++odd_cnt;
                    odd_dig = dig;
                }
            }
            if (odd_cnt > 1) continue;
            bool isoddlen = (LL % 2 == 1);
            if (isoddlen != (odd_cnt == 1)) continue;

            // middle and hreq
            string midd = "";
            vector<int> temp_counts = counts;
            if (isoddlen) {
                midd = string(1, '0' + odd_dig);
                temp_counts[odd_dig]--;
            }
            vector<int> hreq(10, 0);
            for (int dig = 1; dig <= 9; ++dig) {
                hreq[dig] = temp_counts[dig] / 2;
            }
            int hh = LL / 2;

            // small fh
            string fh_small;
            for (int dig = 1; dig <= 9; ++dig) {
                fh_small.append(hreq[dig], '0' + dig);
            }
            string rev_small = fh_small;
            reverse(rev_small.begin(), rev_small.end());
            string pal_small = fh_small + midd + rev_small;

            string cand = "";
            if (LL != static_cast<int>(dd)) {
                if (LL > dd) {
                    cand = pal_small;
                }
            } else {
                if (pal_small > T) {
                    cand = pal_small;
                } else {
                    // dfs for next
                    auto dfs = [&](auto&& self, int pos, string& current, vector<int>& rem,
                                   string& result, bool& found, const string& TT, const string& mm,
                                   int hhh) -> void {
                        if (found) return;
                        if (pos == hhh) {
                            string fh_rev = current;
                            reverse(fh_rev.begin(), fh_rev.end());
                            string full = current + mm + fh_rev;
                            if (full > TT) {
                                result = full;
                                found = true;
                            }
                            return;
                        }
                        for (int dig = 1; dig <= 9; ++dig) {
                            if (rem[dig] > 0 && !found) {
                                rem[dig]--;
                                current.push_back('0' + dig);
                                self(self, pos + 1, current, rem, result, found, TT, mm, hhh);
                                current.pop_back();
                                rem[dig]++;
                                if (found) return;
                            }
                        }
                    };

                    string result = "";
                    bool fnd = false;
                    string curr = "";
                    vector<int> rrem(10, 0);
                    for (int digg = 1; digg <= 9; ++digg) rrem[digg] = hreq[digg];
                    dfs(dfs, 0, curr, rrem, result, fnd, T, midd, hh);
                    if (fnd) {
                        cand = result;
                    }
                }
            }

            if (!cand.empty()) {
                if (best.empty() ||
                    (cand.size() < best.size() ||
                     (cand.size() == best.size() && cand < best))) {
                    best = cand;
                }
            }
        }
        return stoll(best);
    }
};
# @lc code=end