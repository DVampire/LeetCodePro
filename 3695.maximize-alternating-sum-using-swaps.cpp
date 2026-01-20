#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        // Disjoint Set Union (DSU) Find function with path compression
        function<int(int)> find = [&](int i) {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        };

        // Process all allowed swaps to form connected components
        for (const auto& s : swaps) {
            int root_u = find(s[0]);
            int root_v = find(s[1]);
            if (root_u != root_v) {
                parent[root_u] = root_v;
            }
        }

        // Group values and count even/odd index positions for each component
        vector<vector<int>> comp_vals(n);
        vector<int> comp_even_count(n, 0);

        for (int i = 0; i < n; ++i) {
            int r = find(i);
            comp_vals[r].push_back(nums[i]);
            if (i % 2 == 0) {
                comp_even_count[r]++;
            }
        }

        long long total_max_sum = 0;

        // Calculate the maximum contribution of each component
        for (int i = 0; i < n; ++i) {
            if (comp_vals[i].empty()) continue;

            sort(comp_vals[i].begin(), comp_vals[i].end());
            
            int total_count = comp_vals[i].size();
            int even_count = comp_even_count[i];
            int odd_count = total_count - even_count;

            // To maximize: subtract the smallest 'odd_count' values 
            // and add the largest 'even_count' values.
            for (int j = 0; j < total_count; ++j) {
                if (j < odd_count) {
                    total_max_sum -= (long long)comp_vals[i][j];
                } else {
                    total_max_sum += (long long)comp_vals[i][j];
                }
            }
        }

        return total_max_sum;
    }
};
# @lc code=end