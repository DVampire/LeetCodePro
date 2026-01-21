#
# @lc app=leetcode id=3462 lang=cpp
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        int m = grid[0].size();
        
        // Create a list of all elements with their row indices
        vector<pair<int, int>> elements; // (value, row_index)
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                elements.push_back({grid[i][j], i});
            }
        }
        
        // Sort by value in descending order
        sort(elements.begin(), elements.end(), greater<pair<int, int>>());
        
        // Greedily pick elements
        long long sum = 0;
        vector<int> rowCount(n, 0);
        int pickedCount = 0;
        
        for (auto& [val, row] : elements) {
            if (pickedCount >= k) break;
            if (rowCount[row] < limits[row]) {
                sum += val;
                rowCount[row]++;
                pickedCount++;
            }
        }
        
        return sum;
    }
};
# @lc code=end