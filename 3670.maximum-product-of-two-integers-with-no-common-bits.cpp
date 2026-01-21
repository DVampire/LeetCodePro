#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#
# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        // Get unique values and sort in descending order
        set<int> uniqueNums(nums.begin(), nums.end());
        vector<int> unique(uniqueNums.begin(), uniqueNums.end());
        sort(unique.rbegin(), unique.rend());
        
        long long maxProd = 0;
        int m = unique.size();
        
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                long long prod = (long long)unique[i] * unique[j];
                if (prod <= maxProd) {
                    break; // All subsequent products will be even smaller
                }
                if ((unique[i] & unique[j]) == 0) {
                    maxProd = prod;
                    break; // Found the best match for unique[i]
                }
            }
        }
        
        return maxProd;
    }
};
# @lc code=end