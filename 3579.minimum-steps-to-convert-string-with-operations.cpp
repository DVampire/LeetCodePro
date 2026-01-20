#
# @lc app=leetcode id=3579 lang=cpp
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.length();
        vector<int> dp(n + 1, 1e9);
        dp[0] = 0;

        auto get_cost = [&](int start, int len) {
            string s1 = word1.substr(start, len);
            string s2 = word2.substr(start, len);
            if (s1 == s2) return 0;

            // Count character differences for Replace operations
            vector<int> count1(26, 0), count2(26, 0);
            for (char c : s1) count1[c - 'a']++;
            for (char c : s2) count2[c - 'a']++;

            int diff = 0;
            for (int i = 0; i < 26; ++i) {
                if (count1[i] > count2[i]) diff += count1[i] - count2[i];
            }

            // If we can transform s1 to s2 using only replaces
            int replace_only = 0;
            for (int i = 0; i < len; ++i) if (s1[i] != s2[i]) replace_only++;

            // If we use one rearrangement (Swap or Reverse) plus replaces
            // The rearrangement cost is 1. The number of replaces is 'diff'.
            int with_rearrange = 1 + diff;

            return min(replace_only, with_rearrange);
        };

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] = min(dp[i], dp[j] + get_cost(j, i - j));
            }
        }

        return dp[n];
    }
};
# @lc code=end