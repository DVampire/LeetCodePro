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
        stack<pair<int, int>> st; // (value, steps to be removed)
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            int maxTime = 0;
            // Pop elements that won't kill current element (smaller or equal)
            while (!st.empty() && st.top().first <= nums[i]) {
                maxTime = max(maxTime, st.top().second);
                st.pop();
            }
            // If stack is not empty, top is the killer of current element
            // Current element will be removed after all elements between are removed
            int curTime = st.empty() ? 0 : maxTime + 1;
            ans = max(ans, curTime);
            st.push({nums[i], curTime});
        }
        
        return ans;
    }
};
# @lc code=end