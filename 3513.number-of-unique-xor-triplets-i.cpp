#
# @lc app=leetcode id=3513 lang=cpp
#
# [3513] Number of Unique XOR Triplets I
#
# @lc code=start
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        unordered_set<int> uniqueXors;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                for (int k = j; k < n; k++) {
                    int xorVal = nums[i] ^ nums[j] ^ nums[k];
                    uniqueXors.insert(xorVal);
                }
            }
        }
        
        return uniqueXors.size();
    }
};
# @lc code=end