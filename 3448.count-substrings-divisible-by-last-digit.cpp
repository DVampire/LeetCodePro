#
# @lc app=leetcode id=3448 lang=cpp
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        long long ans = 0;
        // dp[m][r] stores the number of substrings ending at the previous position
        // that have a remainder r when divided by m.
        // m ranges from 1 to 9. r ranges from 0 to m-1.
        long long dp[10][10] = {0};
        
        for (char c : s) {
            int digit = c - '0';
            long long next_dp[10][10] = {0};
            
            for (int m = 1; m <= 9; ++m) {
                // Extend existing substrings ending at the previous position
                for (int r = 0; r < m; ++r) {
                    if (dp[m][r] > 0) {
                        int new_rem = (r * 10 + digit) % m;
                        next_dp[m][new_rem] += dp[m][r];
                    }
                }
                // Start a new substring with the current digit itself
                next_dp[m][digit % m]++;
            }
            
            // Update the DP table for the next iteration
            for (int m = 1; m <= 9; ++m) {
                for (int r = 0; r < m; ++r) {
                    dp[m][r] = next_dp[m][r];
                }
            }
            
            // If the current digit is non-zero, we count how many substrings
            // ending at this position are divisible by this digit.
            if (digit != 0) {
                ans += dp[digit][0];
            }
        }
        
        return ans;
    }
};
# @lc code=end