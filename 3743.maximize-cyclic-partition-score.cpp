#
# @lc app=leetcode id=3743 lang=cpp
#
# [3743] Maximize Cyclic Partition Score
#
# @lc code=start
class Solution {
public:
    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1) return 0;
        k = min(k, n);
        
        vector<int> prefixMax(n), prefixMin(n), suffixMax(n), suffixMin(n);
        prefixMax[0] = prefixMin[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i-1], nums[i]);
            prefixMin[i] = min(prefixMin[i-1], nums[i]);
        }
        suffixMax[n-1] = suffixMin[n-1] = nums[n-1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMax[i] = max(suffixMax[i+1], nums[i]);
            suffixMin[i] = min(suffixMin[i+1], nums[i]);
        }
        
        vector<vector<long long>> rangeArr(n, vector<long long>(n));
        for (int l = 0; l < n; l++) {
            int curMax = nums[l], curMin = nums[l];
            for (int r = l; r < n; r++) {
                curMax = max(curMax, nums[r]);
                curMin = min(curMin, nums[r]);
                rangeArr[l][r] = curMax - curMin;
            }
        }
        
        const long long NEG_INF = LLONG_MIN / 2;
        
        vector<vector<vector<long long>>> dpSeg(n, vector<vector<long long>>(n, vector<long long>(k + 1, NEG_INF)));
        for (int l = 0; l < n; l++) dpSeg[l][l][1] = 0;
        
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                dpSeg[l][r][1] = rangeArr[l][r];
                for (int m = 2; m <= min(len, k); m++) {
                    for (int p = l + m - 2; p < r; p++) {
                        if (dpSeg[l][p][m-1] > NEG_INF) {
                            dpSeg[l][r][m] = max(dpSeg[l][r][m], dpSeg[l][p][m-1] + rangeArr[p+1][r]);
                        }
                    }
                }
            }
        }
        
        vector<vector<long long>> maxDpSeg(n, vector<long long>(n, NEG_INF));
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                int len = r - l + 1;
                for (int m = 1; m <= min(k - 1, len); m++) {
                    maxDpSeg[l][r] = max(maxDpSeg[l][r], dpSeg[l][r][m]);
                }
            }
        }
        
        long long ans = NEG_INF;
        for (int m = 1; m <= k; m++) {
            ans = max(ans, dpSeg[0][n-1][m]);
        }
        
        if (k >= 2) {
            for (int start = 2; start < n; start++) {
                for (int end = 0; end <= start - 2; end++) {
                    long long wrapMax = max(suffixMax[start], prefixMax[end]);
                    long long wrapMin = min(suffixMin[start], prefixMin[end]);
                    long long wrapRange = wrapMax - wrapMin;
                    
                    int midL = end + 1, midR = start - 1;
                    if (maxDpSeg[midL][midR] > NEG_INF) {
                        ans = max(ans, wrapRange + maxDpSeg[midL][midR]);
                    }
                }
            }
        }
        
        return ans;
    }
};
# @lc code=end