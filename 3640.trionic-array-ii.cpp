#include <bits/stdc++.h>
using namespace std;

#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        const long long NEG = -(1LL << 62);
        auto addIfValid = [&](long long a, long long b) -> long long {
            if (a <= NEG / 2) return NEG;
            return a + b;
        };

        long long dp1 = NEG; // inc, len>=2
        long long dp2 = NEG; // inc then dec, both len>=2
        long long dp3 = NEG; // inc then dec then inc, all len>=2
        long long ans = NEG;

        int n = (int)nums.size();
        for (int i = 1; i < n; i++) {
            long long new1 = NEG, new2 = NEG, new3 = NEG;

            if (nums[i - 1] < nums[i]) {
                // dp1: start new (i-1,i) or extend previous increasing
                new1 = max((long long)nums[i - 1] + nums[i], addIfValid(dp1, nums[i]));

                // dp3: extend final increasing, or start final increasing from dp2
                new3 = max(addIfValid(dp3, nums[i]), addIfValid(dp2, nums[i]));
            }
            if (nums[i - 1] > nums[i]) {
                // dp2: extend decreasing, or start decreasing from dp1
                new2 = max(addIfValid(dp2, nums[i]), addIfValid(dp1, nums[i]));
            }

            dp1 = new1;
            dp2 = new2;
            dp3 = new3;
            ans = max(ans, dp3);
        }

        return ans;
    }
};
# @lc code=end
