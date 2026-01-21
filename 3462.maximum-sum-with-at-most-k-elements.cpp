#
# @lc app=leetcode id=3462 lang=cpp
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        vector<int> candidates;
        
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            // Sort row in descending order
            sort(grid[i].begin(), grid[i].end(), greater<int>());
            
            // Take top limits[i] elements from this row
            for (int j = 0; j < limits[i]; j++) {
                candidates.push_back(grid[i][j]);
            }
        }
        
        // Sort all candidates in descending order
        sort(candidates.begin(), candidates.end(), greater<int>());
        
        // Sum top k elements
        long long sum = 0;
        for (int i = 0; i < k; i++) {
            sum += candidates[i];
        }
        
        return sum;
    }
};
# @lc code=end