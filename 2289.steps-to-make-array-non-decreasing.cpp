#
# @lc app=leetcode id=2289 lang=cpp
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        // Stack stores pairs of {value, steps_to_be_removed}
        stack<pair<int, int>> st;
        
        for (int i = 0; i < n; ++i) {
            int current_steps = 0;
            // Pop elements that this current element 'protects' or 'stops'
            // from being eaten by elements further to the left.
            while (!st.empty() && st.top().first <= nums[i]) {
                current_steps = max(current_steps, st.top().second);
                st.pop();
            }
            
            // If the stack is empty, no element to the left is greater than nums[i].
            // Otherwise, the element at the top will eventually eat nums[i].
            if (st.empty()) {
                current_steps = 0;
            } else {
                // It takes one more step than the time taken to clear elements in between.
                current_steps = current_steps + 1;
            }
            
            ans = max(ans, current_steps);
            st.push({nums[i], current_steps});
        }
        
        return ans;
    }
};
# @lc code=end