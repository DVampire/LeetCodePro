#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = s.length();
        // can_empty[i][j] is true if substring s[i...j] can be reduced to ""
        vector<vector<bool>> can_empty(n + 1, vector<bool>(n + 1, false));

        // Base case: empty string is empty
        for (int i = 0; i <= n; ++i) {
            can_empty[i][i - 1] = true;
        }

        // DP to find all substrings that can be reduced to ""
        for (int len = 2; len <= n; len += 2) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                for (int k = i + 1; k <= j; k += 2) {
                    if (is_consecutive(s[i], s[k]) && can_empty[i + 1][k - 1] && can_empty[k + 1][j]) {
                        can_empty[i][j] = true;
                        break;
                    }
                }
            }
        }

        // f[i] is the lexicographically smallest string possible from s[i...n-1]
        vector<string> f(n + 1);
        f[n] = "";
        for (int i = n - 1; i >= 0; --i) {
            // Option 1: Keep current character s[i]
            f[i] = s[i] + f[i + 1];
            
            // Option 2: Remove s[i] by pairing it with some s[k]
            for (int k = i + 1; k < n; k += 2) {
                if (can_empty[i][k]) {
                    if (f[k + 1] < f[i]) {
                        f[i] = f[k + 1];
                    }
                }
            }
        }

        return f[0];
    }

private:
    bool is_consecutive(char a, char b) {
        int diff = abs(a - b);
        return diff == 1 || diff == 25;
    }
};
# @lc code=end