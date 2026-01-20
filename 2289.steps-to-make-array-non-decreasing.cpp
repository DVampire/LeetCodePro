#
# @lc app=leetcode id=2289 lang=cpp
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        // Stack stores pairs of {value, steps_to_remove}
        stack<pair<int, int>> s;
        
        for (int i = 0; i < n; ++i) {
            int current_steps = 0;
            // While current element is greater than or equal to the top of the stack,
            // it means the current element 'survives' longer than the top element.
            // We need to account for the time it took to remove those elements.
            while (!s.empty() && nums[i] >= s.top().first) {
                current_steps = max(current_steps, s.top().second);
                s.pop();
            }
            
            // If the stack is empty, there's no element to the left larger than nums[i].
            // So nums[i] will never be removed.
            if (s.empty()) {
                current_steps = 0;
            } else {
                // Otherwise, it is eventually removed by the element currently at the top.
                // It takes one more step than the maximum steps of elements removed between them.
                current_steps++;
            }
            
            ans = max(ans, current_steps);
            s.push({nums[i], current_steps});
        }
        
        return ans;
    }
};
# @lc code=end