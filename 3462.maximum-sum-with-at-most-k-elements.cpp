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
        
        // Step 1: Collect valid candidates from each row based on row limits
        for (int i = 0; i < n; ++i) {
            // Sort the row in descending order to pick the largest elements
            sort(grid[i].rbegin(), grid[i].rend());
            
            // We can take at most limits[i] elements from this row
            int count = limits[i];
            for (int j = 0; j < count && j < grid[i].size(); ++j) {
                candidates.push_back(grid[i][j]);
            }
        }
        
        // Step 2: Sort all collected candidates in descending order
        sort(candidates.rbegin(), candidates.rend());
        
        // Step 3: Pick the top k elements (or fewer if we don't have enough candidates)
        long long totalSum = 0;
        int selections = min((int)candidates.size(), k);
        
        for (int i = 0; i < selections; ++i) {
            totalSum += candidates[i];
        }
        
        return totalSum;
    }
};
# @lc code=end