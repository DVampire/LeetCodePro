#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3503 lang=cpp
 *
 * [3503] Longest Palindrome After Substring Concatenation I
 */

// @lc code=start
class Solution {
public:
    int longestPalindrome(string s, string t) {
        int n = (int)s.size(), m = (int)t.size();

        // store substrings as (start, length), include empty substring
        vector<pair<int,int>> subS, subT;
        subS.reserve(n * (n + 1) / 2 + 1);
        subT.reserve(m * (m + 1) / 2 + 1);

        subS.push_back({0, 0});
        for (int i = 0; i < n; i++) {
            for (int len = 1; i + len <= n; len++) {
                subS.push_back({i, len});
            }
        }

        subT.push_back({0, 0});
        for (int i = 0; i < m; i++) {
            for (int len = 1; i + len <= m; len++) {
                subT.push_back({i, len});
            }
        }

        auto isPalConcat = [&](int si, int sl, int ti, int tl) -> bool {
            int L = sl + tl;
            int l = 0, r = L - 1;
            while (l < r) {
                char cl = (l < sl) ? s[si + l] : t[ti + (l - sl)];
                char cr = (r < sl) ? s[si + r] : t[ti + (r - sl)];
                if (cl != cr) return false;
                ++l; --r;
            }
            return true;
        };

        int best = 0;
        for (auto [si, sl] : subS) {
            for (auto [ti, tl] : subT) {
                int L = sl + tl;
                if (L <= best) continue;
                if (isPalConcat(si, sl, ti, tl)) best = L;
            }
        }
        return best;
    }
};
// @lc code=end
