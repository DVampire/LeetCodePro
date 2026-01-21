#
# @lc app=leetcode id=3579 lang=cpp
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        const int INF = 1000;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        auto cost = [&](int l, int r, const string& w1, const string& w2) -> int {
            int m = r - l;
            // no reverse
            vector<vector<int>> cnt(26, vector<int>(26, 0));
            int H = 0;
            for (int k = l; k < r; ++k) {
                int x = w1[k] - 'a';
                int y = w2[k] - 'a';
                if (x != y) {
                    cnt[x][y]++;
                    ++H;
                }
            }
            int K = 0;
            for (int x = 0; x < 26; ++x) {
                for (int y = x + 1; y < 26; ++y) {
                    K += min(cnt[x][y], cnt[y][x]);
                }
            }
            int ops_no = H - K;
            // with reverse
            vector<vector<int>> cnt_rev(26, vector<int>(26, 0));
            int H_rev = 0;
            for (int ii = 0; ii < m; ++ii) {
                int k_from = l + (m - 1 - ii);
                int x = w1[k_from] - 'a';
                int y = w2[l + ii] - 'a';
                if (x != y) {
                    cnt_rev[x][y]++;
                    ++H_rev;
                }
            }
            int K_rev = 0;
            for (int x = 0; x < 26; ++x) {
                for (int y = x + 1; y < 26; ++y) {
                    K_rev += min(cnt_rev[x][y], cnt_rev[y][x]);
                }
            }
            int ops_r = H_rev - K_rev + 1;
            return min(ops_no, ops_r);
        };
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                int c = cost(j, i, word1, word2);
                if (dp[j] < INF) {
                    dp[i] = min(dp[i], dp[j] + c);
                }
            }
        }
        return dp[n];
    }
};
# @lc code=end