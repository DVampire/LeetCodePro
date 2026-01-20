#
# @lc app=leetcode id=3420 lang=cpp
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

# @lc code=start
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long current_cost = 0;
        int r = n - 1;
        // Deque stores pairs of {prefix_max_value, count_of_elements_having_this_prefix_max}
        deque<pair<int, int>> dq;

        for (int l = n - 1; l >= 0; --l) {
            int new_val_count = 1;
            // When adding nums[l] to the front, it might become the new prefix maximum
            // for subsequent elements in the window that previously had a smaller prefix max.
            while (!dq.empty() && dq.front().first < nums[l]) {
                current_cost += (long long)(nums[l] - dq.front().first) * dq.front().second;
                new_val_count += dq.front().second;
                dq.pop_front();
            }
            dq.push_front({nums[l], new_val_count});

            // If the cost to make nums[l...r] non-decreasing exceeds k, shrink from the right.
            while (current_cost > k) {
                // The prefix max for nums[r] is the value at the back of the deque.
                current_cost -= (dq.back().first - nums[r]);
                dq.back().second--;
                if (dq.back().second == 0) {
                    dq.pop_back();
                }
                r--;
            }
            
            // All subarrays starting at l and ending at any index from l to r are valid.
            ans += (r - l + 1);
        }

        return ans;
    }
};
# @lc code=end