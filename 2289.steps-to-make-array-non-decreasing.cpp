#
# @lc app=leetcode id=2289 lang=cpp
#
# [2289] Steps to Make Array Non-decreasing
#
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

# @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        // stack holds pairs: {value, steps_when_this_value_is_removed}
        vector<pair<int,int>> st;
        st.reserve(nums.size());
        int ans = 0;

        for (int x : nums) {
            int days = 0;

            while (!st.empty() && x >= st.back().first) {
                days = max(days, st.back().second);
                st.pop_back();
            }

            int dp = 0;
            if (!st.empty()) {
                dp = days + 1;
            }

            ans = max(ans, dp);
            st.push_back({x, dp});
        }

        return ans;
    }
};
# @lc code=end
