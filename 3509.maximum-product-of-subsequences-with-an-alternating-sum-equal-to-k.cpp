#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();
        const int OFFSET = 1800;
        const int MAXS = 3600;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(MAXS + 1, vector<int>(2, -1)));
        vector<vector<vector<char>>> exc(n + 1, vector<vector<char>>(MAXS + 1, vector<char>(2, 0)));
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            // transitions
            for (int ss = 0; ss <= MAXS; ++ss) {
                for (int p = 0; p < 2; ++p) {
                    int valid = dp[i][ss][p];
                    char has_e = exc[i][ss][p];
                    if (valid == -1 && has_e == 0) continue;
                    int curs = ss - OFFSET;
                    // skip
                    {
                        if (valid != -1) {
                            dp[i + 1][ss][p] = max(dp[i + 1][ss][p], valid);
                        }
                        if (has_e) {
                            exc[i + 1][ss][p] = 1;
                        }
                    }
                    // take
                    int sign = (p == 0 ? 1 : -1);
                    int news = curs + sign * x;
                    int nss = news + OFFSET;
                    if (nss >= 0 && nss <= MAXS) {
                        int np = 1 - p;
                        // from valid
                        if (valid != -1) {
                            long long nprod = 1LL * valid * x;
                            if (nprod <= limit) {
                                dp[i + 1][nss][np] = max(dp[i + 1][nss][np], (int)nprod);
                            } else {
                                exc[i + 1][nss][np] = 1;
                            }
                        }
                        // from exc
                        if (has_e) {
                            if (x == 0) {
                                dp[i + 1][nss][np] = max(dp[i + 1][nss][np], 0);
                            } else {
                                exc[i + 1][nss][np] = 1;
                            }
                        }
                    }
                }
            }
            // start new
            {
                int starts = x + OFFSET;
                if (starts >= 0 && starts <= MAXS) {
                    long long nprod = x;
                    if (nprod <= limit) {
                        dp[i + 1][starts][1] = max(dp[i + 1][starts][1], (int)nprod);
                    }
                }
            }
        }
        int ts = k + OFFSET;
        int ans = -1;
        if (ts >= 0 && ts <= MAXS) {
            ans = max(dp[n][ts][0], dp[n][ts][1]);
        }
        return ans;
    }
};
# @lc code=end