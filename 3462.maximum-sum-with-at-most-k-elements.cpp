#
# @lc app=leetcode id=3462 lang=cpp
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        vector<int> all_candidates;

        // Step 1: For each row, identify the best candidates to pick.
        // We can take at most limits[i] elements from row i. 
        // To maximize the sum, we should pick the largest ones available in that row.
        for (int i = 0; i < n; ++i) {
            // Sort the row in descending order
            sort(grid[i].begin(), grid[i].end(), greater<int>());
            
            // Take the top 'limits[i]' elements from this row
            int count_to_take = limits[i];
            // Since 0 <= limits[i] <= m, count_to_take is at most the row size.
            for (int j = 0; j < count_to_take; ++j) {
                all_candidates.push_back(grid[i][j]);
            }
        }

        // Step 2: From all potential candidates across all rows, pick the top k.
        // Sort the entire candidate pool in descending order.
        sort(all_candidates.begin(), all_candidates.end(), greater<int>());

        // Step 3: Calculate the maximum sum by picking the largest k elements.
        long long total_sum = 0;
        // Per constraints, k <= sum(limits), so all_candidates.size() is at least k.
        // Also, all elements are non-negative, so taking exactly k elements is optimal.
        for (int i = 0; i < k && i < all_candidates.size(); ++i) {
            total_sum += (long long)all_candidates[i];
        }

        return total_sum;
    }
};
# @lc code=end