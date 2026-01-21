#
# @lc app=leetcode id=3434 lang=cpp
#
# [3434] Maximum Frequency After Subarray Operation
#
# @lc code=start
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        int total_k = count(nums.begin(), nums.end(), k);
        int result = total_k;
        
        // For each possible value v that we want to convert to k
        for (int v = 1; v <= 50; v++) {
            if (v == k) continue;
            
            // Kadane's algorithm to find max subarray sum
            // where +1 for v's and -1 for k's
            int max_sum = 0, cur_sum = 0;
            for (int i = 0; i < n; i++) {
                int contribution = 0;
                if (nums[i] == v) contribution = 1;
                else if (nums[i] == k) contribution = -1;
                
                cur_sum = max(0, cur_sum + contribution);
                max_sum = max(max_sum, cur_sum);
            }
            result = max(result, total_k + max_sum);
        }
        
        return result;
    }
};
# @lc code=end