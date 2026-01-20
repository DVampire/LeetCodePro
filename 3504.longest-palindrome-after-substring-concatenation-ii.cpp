#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#
# @lc app=leetcode id=3504 lang=cpp
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
class SAM {
public:
    struct Node {
        int len, link;
        map<char, int> next;
    };
    vector<Node> st;
    int last;

    SAM(string s) {
        st.push_back({0, -1, {}});
        last = 0;
        for (char c : s) extend(c);
    }

    void extend(char c) {
        int cur = st.size();
        st.push_back({st[last].len + 1, 0, {}});
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back({st[p].len + 1, st[q].link, st[q].next});
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};

class Solution {
public:
    int longestPalindrome(string s, string t) {
        int n = s.length();
        int m = t.length();

        auto getPal = [](string str) {
            int len = str.length();
            vector<vector<bool>> dp(len, vector<bool>(len, false));
            for (int i = len - 1; i >= 0; i--) {
                dp[i][i] = true;
                for (int j = i + 1; j < len; j++) {
                    if (str[i] == str[j]) {
                        dp[i][j] = (j - i == 1) ? true : dp[i + 1][j - 1];
                    }
                }
            }
            return dp;
        };

        vector<vector<bool>> isPalS = getPal(s);
        vector<vector<bool>> isPalT = getPal(t);

        vector<int> maxPalSStartingAt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalS[i][j]) maxPalSStartingAt[i] = max(maxPalSStartingAt[i], j - i + 1);
            }
        }

        vector<int> maxPalTEndingAt(m, 0);
        for (int j = 0; j < m; j++) {
            for (int i = 0; i <= j; i++) {
                if (isPalT[i][j]) maxPalTEndingAt[j] = max(maxPalTEndingAt[j], j - i + 1);
            }
        }

        SAM samT(t);
        vector<int> f(n, 0);
        int curr = 0, l = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            while (curr != 0 && !samT.st[curr].next.count(c)) {
                curr = samT.st[curr].link;
                l = samT.st[curr].len;
            }
            if (samT.st[curr].next.count(c)) {
                curr = samT.st[curr].next[c];
                l++;
            }
            // We need the longest suffix of s[0..i] whose REVERSE is in t.
            // So we actually need to process characters of s in reverse for each i.
        }

        // Correct approach for f(k) and g(k) with N=1000:
        auto getLongestReverseIn = [](string src, string target, bool suffix) {
            int n_src = src.length();
            vector<int> res(n_src, 0);
            for (int i = 0; i < n_src; i++) {
                string sub = "";
                if (suffix) {
                    for (int j = i; j >= 0; j--) {
                        sub += src[j];
                        if (target.find(sub) != string::npos) res[i] = sub.length();
                        else break;
                    }
                } else {
                    for (int j = i; j < n_src; j++) {
                        sub += src[j];
                        string rev = sub; reverse(rev.begin(), rev.end());
                        if (target.find(rev) != string::npos) res[i] = sub.length();
                        else break;
                    }
                }
            }
            return res;
        };

        vector<int> fk = getLongestReverseIn(s, t, true);
        vector<int> gk = getLongestReverseIn(t, s, false);

        int ans = 0;
        for (int k = 0; k <= n; k++) {
            int prefixLen = (k == 0) ? 0 : fk[k - 1];
            int palLen = (k == n) ? 0 : maxPalSStartingAt[k];
            ans = max(ans, 2 * prefixLen + palLen);
        }
        for (int k = -1; k < m; k++) {
            int suffixLen = (k == m - 1) ? 0 : gk[k + 1];
            int palLen = (k == -1) ? 0 : maxPalTEndingAt[k];
            ans = max(ans, 2 * suffixLen + palLen);
        }

        return ans;
    }
};
# @lc code=end