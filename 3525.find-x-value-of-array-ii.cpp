#
# @lc app=leetcode id=3525 lang=cpp
#
# [3525] Find X Value of Array II
#
# @lc code=start
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        vector<int> result;
        
        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int x = query[3];
            
            // Update nums (persists for subsequent queries)
            nums[index] = value;
            
            // Count the number of ways to remove a suffix such that
            // the product of remaining elements has remainder x modulo k
            int count = 0;
            long long product = 1;
            
            for (int i = start; i < nums.size(); i++) {
                product = (product * nums[i]) % k;
                if (product == x) {
                    count++;
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};
# @lc code=end