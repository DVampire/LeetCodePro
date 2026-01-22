#
# @lc app=leetcode id=3704 lang=cpp
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution {
public:
    long long countNoZeroPairs(long long n) {
        string s = to_string(n);
        int k = s.size();
        reverse(s.begin(), s.end()); // s[i] is the i-th digit from LSB
        
        long long ans = 0;
        
        for (int len_a = 1; len_a <= k; len_a++) {
            for (int len_b = 1; len_b <= k; len_b++) {
                int max_pos = max({len_a, len_b, k});
                vector<long long> dp(2, 0);
                dp[0] = 1;
                
                for (int pos = 0; pos < max_pos; pos++) {
                    int n_digit = (pos < k) ? (s[pos] - '0') : 0;
                    
                    int a_min = (pos < len_a) ? 1 : 0;
                    int a_max = (pos < len_a) ? 9 : 0;
                    int b_min = (pos < len_b) ? 1 : 0;
                    int b_max = (pos < len_b) ? 9 : 0;
                    
                    vector<long long> dp_next(2, 0);
                    
                    for (int carry_in = 0; carry_in <= 1; carry_in++) {
                        if (dp[carry_in] == 0) continue;
                        
                        for (int carry_out = 0; carry_out <= 1; carry_out++) {
                            int sum = n_digit + 10 * carry_out - carry_in;
                            
                            int lo = max(a_min, sum - b_max);
                            int hi = min(a_max, sum - b_min);
                            if (lo > hi) continue;
                            long long ways = hi - lo + 1;
                            
                            dp_next[carry_out] += dp[carry_in] * ways;
                        }
                    }
                    
                    dp = dp_next;
                }
                
                ans += dp[0];
            }
        }
        
        return ans;
    }
};
# @lc code=end