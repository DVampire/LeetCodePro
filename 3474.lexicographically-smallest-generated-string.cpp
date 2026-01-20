#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        string word(len, '?');
        vector<bool> fixed(len, false);

        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    if (word[i + j] != '?' && word[i + j] != str2[j]) return "";
                    word[i + j] = str2[j];
                    fixed[i + j] = true;
                }
            }
        }

        for (int i = 0; i < len; ++i) {
            if (word[i] == '?') word[i] = 'a';
        }

        auto check = [&](int i) {
            if (i < 0 || i >= n) return true;
            for (int j = 0; j < m; ++j) {
                if (word[i + j] != str2[j]) return true;
            }
            return false;
        };

        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'F' && !check(i)) {
                bool resolved = false;
                for (int j = m - 1; j >= 0; --j) {
                    if (!fixed[i + j]) {
                        char original = word[i + j];
                        for (char c = 'b'; c <= 'z'; ++c) {
                            word[i + j] = c;
                            bool ok = true;
                            for (int k = max(0, i + j - m + 1); k <= min(n - 1, i + j); ++k) {
                                if (str1[k] == 'T' && !(!check(k))) { ok = false; break; }
                            }
                            if (ok) {
                                resolved = true;
                                break;
                            }
                        }
                        if (resolved) break;
                        word[i + j] = original;
                    }
                }
                if (!resolved) return "";
            }
        }

        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T' && check(i)) return "";
            if (str1[i] == 'F' && !check(i)) return "";
        }

        return word;
    }
};