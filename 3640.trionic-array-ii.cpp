#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#
# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(3, LLONG_MIN));
        
        long long answer = LLONG_MIN;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    // Extend or start increasing phase (state 0)
                    if (dp[j][0] == LLONG_MIN) {
                        dp[i][0] = max(dp[i][0], (long long)nums[j] + nums[i]);
                    } else {
                        dp[i][0] = max(dp[i][0], dp[j][0] + nums[i]);
                    }
                    
                    // Transition from dec to final inc, or extend final inc (state 2)
                    if (dp[j][1] != LLONG_MIN) {
                        dp[i][2] = max(dp[i][2], dp[j][1] + nums[i]);
                    }
                    if (dp[j][2] != LLONG_MIN) {
                        dp[i][2] = max(dp[i][2], dp[j][2] + nums[i]);
                    }
                } else if (nums[j] > nums[i]) {
                    // Transition from inc to dec, or extend dec (state 1)
                    if (dp[j][0] != LLONG_MIN) {
                        dp[i][1] = max(dp[i][1], dp[j][0] + nums[i]);
                    }
                    if (dp[j][1] != LLONG_MIN) {
                        dp[i][1] = max(dp[i][1], dp[j][1] + nums[i]);
                    }
                }
            }
            
            if (dp[i][2] != LLONG_MIN) {
                answer = max(answer, dp[i][2]);
            }
        }
        
        return answer;
    }
};
# @lc code=end