#
# @lc app=leetcode id=3504 lang=cpp
#
# [3504] Longest Palindrome After Substring Concatenation II
#
# @lc code=start
class Solution {
public:
    int longestPalindrome(string s, string t) {
        int maxLen = 0;
        int n = s.length(), m = t.length();
        
        // Precompute palindrome checks using [i, j) intervals
        vector<vector<bool>> is_pal_s(n + 1, vector<bool>(n + 1, false));
        vector<vector<bool>> is_pal_t(m + 1, vector<bool>(m + 1, false));
        
        // Empty strings and single characters are palindromes
        for (int i = 0; i <= n; i++) is_pal_s[i][i] = true;
        for (int i = 0; i < n; i++) is_pal_s[i][i + 1] = true;
        for (int i = 0; i <= m; i++) is_pal_t[i][i] = true;
        for (int i = 0; i < m; i++) is_pal_t[i][i + 1] = true;
        
        // Build palindrome tables
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len;
                if (s[i] == s[j - 1] && (len == 2 || is_pal_s[i + 1][j - 1])) {
                    is_pal_s[i][j] = true;
                }
            }
        }
        
        for (int len = 2; len <= m; len++) {
            for (int i = 0; i + len <= m; i++) {
                int j = i + len;
                if (t[i] == t[j - 1] && (len == 2 || is_pal_t[i + 1][j - 1])) {
                    is_pal_t[i][j] = true;
                }
            }
        }
        
        // Try all combinations
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                for (int p = 0; p <= m; p++) {
                    for (int q = p; q <= m; q++) {
                        int len_s = j - i;
                        int len_t = q - p;
                        
                        if (len_s == 0 && len_t == 0) continue;
                        
                        bool valid = true;
                        int match_len = min(len_s, len_t);
                        
                        // Check matching part
                        for (int k = 0; k < match_len; k++) {
                            if (s[i + k] != t[q - 1 - k]) {
                                valid = false;
                                break;
                            }
                        }
                        
                        if (!valid) continue;
                        
                        // Check middle palindrome
                        if (len_s > len_t && !is_pal_s[i + len_t][j]) {
                            valid = false;
                        } else if (len_t > len_s && !is_pal_t[p][q - len_s]) {
                            valid = false;
                        }
                        
                        if (valid) {
                            maxLen = max(maxLen, len_s + len_t);
                        }
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end