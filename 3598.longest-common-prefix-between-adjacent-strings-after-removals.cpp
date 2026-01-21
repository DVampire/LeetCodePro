#
# @lc app=leetcode id=3598 lang=cpp
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
class Solution {
public:
    int get_lcp(const string& a, const string& b) {
        int len = min((int)a.size(), (int)b.size());
        for (int k = 0; k < len; ++k) {
            if (a[k] != b[k]) return k;
        }
        return len;
    }

    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        if (n == 1) return {0};
        int m = n - 1;
        vector<int> prefix_len(m);
        for (int j = 0; j < m; ++j) {
            prefix_len[j] = get_lcp(words[j], words[j + 1]);
        }
        vector<int> logg(m + 2, 0);
        logg[1] = 0;
        for (int i = 2; i <= m; ++i) {
            logg[i] = logg[i / 2] + 1;
        }
        const int MAXLOG = 18;
        vector<vector<int>> st(MAXLOG, vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            st[0][i] = prefix_len[i];
        }
        for (int j = 1; j < MAXLOG; ++j) {
            for (int i = 0; i + (1 << j) <= m; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
        auto query = [&](int L, int R) -> int {
            if (L > R) return 0;
            int len = R - L + 1;
            int k = logg[len];
            return max(st[k][L], st[k][R - (1 << k) + 1]);
        };
        vector<int> answer(n);
        for (int i = 0; i < n; ++i) {
            int cand = 0;
            if (i >= 2) {
                cand = max(cand, query(0, i - 2));
            }
            if (i + 1 <= m - 1) {
                cand = max(cand, query(i + 1, m - 1));
            }
            if (i > 0 && i < n - 1) {
                int newl = get_lcp(words[i - 1], words[i + 1]);
                cand = max(cand, newl);
            }
            answer[i] = cand;
        }
        return answer;
    }
};
# @lc code=end