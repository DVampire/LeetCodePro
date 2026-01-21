#
# @lc app=leetcode id=3734 lang=cpp
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#

# @lc code=start
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string lexPalindromicPermutation(std::string s, std::string target) {
        int n = s.size();
        std::vector<int> freq(26, 0);
        for (char ch : s) {
            freq[ch - 'a']++;
        }
        int m = n / 2;
        std::vector<int> num_L(26, 0);
        char mid_char = 0;
        int odd_cnt = 0;
        for (int i = 0; i < 26; i++) {
            num_L[i] = freq[i] / 2;
            if (freq[i] % 2 == 1) {
                odd_cnt++;
                mid_char = 'a' + i;
            }
        }
        if ((n % 2 == 1 && odd_cnt != 1) || (n % 2 == 0 && odd_cnt != 0)) {
            return "";
        }

        std::string T_left = target.substr(0, m);
        std::vector<int> count_T(26, 0);
        for (char ch : T_left) {
            count_T[ch - 'a']++;
        }
        bool valid_T = true;
        for (int i = 0; i < 26; i++) {
            if (count_T[i] != num_L[i]) {
                valid_T = false;
                break;
            }
        }

        auto build = [&](const std::string& L) -> std::string {
            std::string P(n, '*');
            for (int i = 0; i < m; i++) {
                P[i] = L[i];
                P[n - 1 - i] = L[i];
            }
            if (n % 2 == 1) {
                P[m] = mid_char;
            }
            return P;
        };

        if (valid_T) {
            std::string P = build(T_left);
            if (P > target) {
                return P;
            }
        }

        // Get next L > T_left
        std::string nextL = get_next_perm_greater(T_left, num_L, m);
        if (nextL.empty()) {
            return "";
        }
        return build(nextL);
    }

private:
    std::string get_next_perm_greater(const std::string& S, const std::vector<int>& counts, int len) {
        std::vector<int> rem = counts;
        std::string X;
        bool still_equal = true;
        for (int i = 0; i < len; i++) {
            bool found = false;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                int idx = ch - 'a';
                if (rem[idx] == 0) continue;
                rem[idx]--;

                int prefix_cmp;
                if (!still_equal) {
                    prefix_cmp = 1;
                } else {
                    char s_ch = S[i];
                    if (ch > s_ch) prefix_cmp = 1;
                    else if (ch < s_ch) prefix_cmp = -1;
                    else prefix_cmp = 0;
                }

                bool can_use = false;
                if (prefix_cmp > 0) {
                    can_use = true;
                } else if (prefix_cmp == 0) {
                    int suf_len = len - i - 1;
                    std::string suf_S = S.substr(i + 1, suf_len);
                    std::vector<int> rem_copy = rem;
                    std::string Ymax(suf_len, ' ');
                    bool can_fill = true;
                    for (int j = 0; j < suf_len; j++) {
                        bool got = false;
                        for (char cc = 'z'; cc >= 'a'; cc--) {
                            int idd = cc - 'a';
                            if (rem_copy[idd] > 0) {
                                Ymax[j] = cc;
                                rem_copy[idd]--;
                                got = true;
                                break;
                            }
                        }
                        if (!got) {
                            can_fill = false;
                            break;
                        }
                    }
                    if (can_fill && Ymax > suf_S) {
                        can_use = true;
                    }
                }

                if (can_use) {
                    X += ch;
                    still_equal = still_equal && (ch == S[i]);
                    found = true;
                    break;
                } else {
                    rem[idx]++;
                }
            }
            if (!found) {
                return "";
            }
        }
        return X;
    }
};
# @lc code=end