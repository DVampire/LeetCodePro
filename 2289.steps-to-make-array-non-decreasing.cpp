#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

//
// @lc app=leetcode id=2289 lang=cpp
//
// [2289] Steps to Make Array Non-decreasing
//

// @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        // stack holds pairs: {value, steps it survives before being removed}
        vector<pair<int,int>> st;
        st.reserve(nums.size());
        int ans = 0;

        for (int i = (int)nums.size() - 1; i >= 0; --i) {
            int curSteps = 0;
            while (!st.empty() && nums[i] > st.back().first) {
                curSteps = max(curSteps + 1, st.back().second);
                st.pop_back();
            }
            ans = max(ans, curSteps);
            st.push_back({nums[i], curSteps});
        }
        return ans;
    }
};
// @lc code=end
