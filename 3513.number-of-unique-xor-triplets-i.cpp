#
# @lc app=leetcode id=3513 lang=cpp
#
# [3513] Number of Unique XOR Triplets I
#

# @lc code=start
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = (int)nums.size();
        if (n < 3) return n; // n=1 ->1, n=2 ->2

        // bit length b such that 2^(b-1) <= n < 2^b
        int b = 32 - __builtin_clz((unsigned)n);
        return 1 << b; // 2^b
    }
};
# @lc code=end
