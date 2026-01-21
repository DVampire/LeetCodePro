#
# @lc app=leetcode id=3504 lang=cpp
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

struct Hash {
    vector<ull> pref1, pow1, pref2, pow2;
    Hash(const string& str, ull b1 = 131, ull b2 = 137) {
        int n = str.size();
        pref1.assign(n + 1, 0);
        pow1.assign(n + 1, 1);
        pref2.assign(n + 1, 0);
        pow2.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pref1[i] = pref1[i - 1] * b1 + (ull)(str[i - 1] - 'a' + 1);
            pow1[i] = pow1[i - 1] * b1;
            pref2[i] = pref2[i - 1] * b2 + (ull)(str[i - 1] - 'a' + 1);
            pow2[i] = pow2[i - 1] * b2;
        }
    }
    pair<ull, ull> get(int l, int r) {
        int len = r - l + 1;
        ull h1 = pref1[r + 1] - pref1[l] * pow1[len];
        ull h2 = pref2[r + 1] - pref2[l] * pow2[len];
        return {h1, h2};
    }
};

int get_lcp(const Hash& h1, int i1, const Hash& h2, int i2) {
    int len1 = h1.pref1.size() - 1 - i1;
    int len2 = h2.pref1.size() - 1 - i2;
    int mx = min(len1, len2);
    int low = 0, high = mx;
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        if (h1.get(i1, i1 + mid - 1) == h2.get(i2, i2 + mid - 1)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

class Solution {
public:
    int longestPalindrome(string s, string t) {
        string rs = s;
        reverse(rs.begin(), rs.end());
        string rt = t;
        reverse(rt.begin(), rt.end());
        int n = s.size(), m = t.size();
        Hash hs(s), hrs(rs), ht(t), hrt(rt);

        // Longest pal starting at each pos in s
        vector<int> pal_s(n);
        for (int st = 0; st < n; ++st) {
            int low = 0, high = n - st;
            while (low < high) {
                int mid = low + (high - low + 1) / 2;
                int endd = st + mid - 1;
                int rl = n - 1 - endd;
                int rr = n - 1 - st;
                if (hs.get(st, endd) == hrs.get(rl, rr)) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            pal_s[st] = low;
        }

        // Longest pal starting at each pos in t
        vector<int> pal_t(m);
        for (int st = 0; st < m; ++st) {
            int low = 0, high = m - st;
            while (low < high) {
                int mid = low + (high - low + 1) / 2;
                int endd = st + mid - 1;
                int rl = m - 1 - endd;
                int rr = m - 1 - st;
                if (ht.get(st, endd) == hrt.get(rl, rr)) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            pal_t[st] = low;
        }

        int ans = 0;
        // Pure s and t covered in loops below

        // Overhang in s (la >= lb)
        vector<int> max_lb(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
                int lc = get_lcp(hs, i, hrt, k);
                if (lc > max_lb[i]) max_lb[i] = lc;
            }
        }
        for (int i = 0; i < n; ++i) {
            int mlb = max_lb[i];
            for (int lb = 0; lb <= mlb; ++lb) {
                int st_over = i + lb;
                int dd;
                if (st_over == n) {
                    dd = 0;
                } else {
                    dd = pal_s[st_over];
                }
                int cand = 2 * lb + dd;
                if (cand > ans) ans = cand;
            }
        }

        // Overhang in t (lb >= la)
        vector<int> max_la(m, 0);
        for (int p = 0; p < m; ++p) {
            for (int u = 0; u < n; ++u) {
                int lc = get_lcp(ht, p, hrs, u);
                if (lc > max_la[p]) max_la[p] = lc;
            }
        }
        for (int p = 0; p < m; ++p) {
            int mla = max_la[p];
            for (int la = 0; la <= mla; ++la) {
                int st_over = p + la;
                int dd;
                if (st_over == m) {
                    dd = 0;
                } else {
                    dd = pal_t[st_over];
                }
                int cand = 2 * la + dd;
                if (cand > ans) ans = cand;
            }
        }

        return ans;
    }
};
# @lc code=end