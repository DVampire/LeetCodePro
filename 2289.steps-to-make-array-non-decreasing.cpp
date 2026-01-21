#
# @lc app=leetcode id=2289 lang=cpp
#
# [2289] Steps to Make Array Non-decreasing
#
# @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        vector<int> steps(n, 0);
        stack<int> st;
        int maxSteps = 0;
        
        for (int i = 0; i < n; i++) {
            int currentSteps = 0;
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                currentSteps = max(currentSteps, steps[st.top()]);
                st.pop();
            }
            if (!st.empty()) {
                steps[i] = currentSteps + 1;
                maxSteps = max(maxSteps, steps[i]);
            }
            st.push(i);
        }
        
        return maxSteps;
    }
};
# @lc code=end