#
# @lc app=leetcode id=3513 lang=cpp
#
# [3513] Number of Unique XOR Triplets I
#

# @lc code=start
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        int l = 31 - __builtin_clz(n);
        return 1 << (l + 1);
    }
};
# @lc code=end
