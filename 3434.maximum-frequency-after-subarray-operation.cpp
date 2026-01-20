#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3434 lang=cpp
 *
 * [3434] Maximum Frequency After Subarray Operation
 */

// @lc code=start
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int totalK = 0;
        for (int x : nums) if (x == k) totalK++;

        int bestOverallGain = 0;

        for (int v = 1; v <= 50; v++) {
            if (v == k) continue;

            int cur = 0, best = 0;
            for (int x : nums) {
                int w = 0;
                if (x == v) w = 1;
                else if (x == k) w = -1;

                cur = max(0, cur + w);
                best = max(best, cur);
            }
            bestOverallGain = max(bestOverallGain, best);
        }

        return totalK + bestOverallGain;
    }
};
// @lc code=end
