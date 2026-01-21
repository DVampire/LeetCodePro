#include <vector>
#include <algorithm>
using namespace std;

/*
 * @lc app=leetcode id=2289 lang=cpp
 *
 * [2289] Steps to Make Array Non-decreasing
 */

// @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        // stack holds pairs: {value, stepsUntilRemoved}
        vector<pair<int,int>> st;
        st.reserve(nums.size());

        int ans = 0;
        for (int x : nums) {
            int cnt = 0;
            while (!st.empty() && x >= st.back().first) {
                cnt = max(cnt, st.back().second);
                st.pop_back();
            }
            int steps = 0;
            if (!st.empty()) steps = cnt + 1;
            ans = max(ans, steps);
            st.push_back({x, steps});
        }
        return ans;
    }
};
// @lc code=end
