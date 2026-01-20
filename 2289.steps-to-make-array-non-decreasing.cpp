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
        // dp[i] stores the number of steps to remove nums[i]
        vector<int> dp(n, 0);
        stack<int> st;
        int maxSteps = 0;

        for (int i = 0; i < n; ++i) {
            int curMax = 0;
            // While the current element is greater than or equal to the top of the stack,
            // it means the current element 'blocks' the top element or comes after it.
            // The top element (and anything smaller before it) must be resolved.
            // We take the max steps from the elements we pop.
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                curMax = max(curMax, dp[st.top()]);
                st.pop();
            }

            // If the stack is not empty, it means there is a previous element strictly greater than nums[i].
            // nums[i] will be removed by that element.
            // It takes 1 step + the max steps of any smaller elements between them.
            if (!st.empty()) {
                dp[i] = curMax + 1;
                maxSteps = max(maxSteps, dp[i]);
            }
            
            st.push(i);
        }

        return maxSteps;
    }
};
# @lc code=end