#
# @lc app=leetcode id=3448 lang=cpp
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        long long count = 0;
        int n = s.length();
        
        for (int j = 0; j < n; j++) {
            int d = s[j] - '0';
            if (d == 0) continue;  // Skip if last digit is 0
            
            long long num = 0;
            long long power = 1;
            for (int i = j; i >= 0; i--) {
                num = (num + (s[i] - '0') * power) % d;
                if (num == 0) {
                    count++;
                }
                power = (power * 10) % d;
            }
        }
        
        return count;
    }
};
# @lc code=end