#
# @lc app=leetcode id=3782 lang=cpp
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#
# @lc code=start
class Solution {
public:
    long long lastInteger(long long n) {
        return solve(n, true);
    }
    
private:
    long long solve(long long n, bool leftToRight) {
        if (n == 1) return 1;
        
        if (leftToRight) {
            return 2 * solve(n / 2, false) - 1;
        } else {
            return 2 * solve(n / 2, true) - (n & 1);
        }
    }
};
# @lc code=end