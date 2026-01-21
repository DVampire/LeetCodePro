#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
    static int matchingFromCounts(const int cnt[26][26]) {
        int m = 0;
        for (int x = 0; x < 26; ++x) {
            for (int y = x + 1; y < 26; ++y) {
                m += min(cnt[x][y], cnt[y][x]);
            }
        }
        return m;
    }

public:
    int minOperations(string word1, string word2) {
        int n = (int)word1.size();
        vector<vector<int>> cost(n, vector<int>(n, 0));

        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                int cnt1[26][26];
                memset(cnt1, 0, sizeof(cnt1));
                int mism1 = 0;
                for (int k = l; k <= r; ++k) {
                    int x = word1[k] - 'a';
                    int y = word2[k] - 'a';
                    if (x != y) mism1++;
                    cnt1[x][y]++;
                }
                int match1 = matchingFromCounts(cnt1);
                int costNoRev = mism1 - match1;

                int cnt2[26][26];
                memset(cnt2, 0, sizeof(cnt2));
                int mism2 = 0;
                int len = r - l + 1;
                for (int t = 0; t < len; ++t) {
                    int x = word1[r - t] - 'a';
                    int y = word2[l + t] - 'a';
                    if (x != y) mism2++;
                    cnt2[x][y]++;
                }
                int match2 = matchingFromCounts(cnt2);
                int costRev = 1 + (mism2 - match2);

                cost[l][r] = min(costNoRev, costRev);
            }
        }

        const int INF = 1e9;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        for (int j = 1; j <= n; ++j) {
            for (int i = 0; i < j; ++i) {
                dp[j] = min(dp[j], dp[i] + cost[i][j - 1]);
            }
        }
        return dp[n];
    }
};
// @lc code=end
