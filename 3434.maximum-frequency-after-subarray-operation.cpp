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

        int bestGain = 0;
        // Try converting each possible value v into k by choosing x = k - v
        for (int v = 1; v <= 50; v++) {
            if (v == k) continue;
            int cur = 0, best = 0;
            for (int a : nums) {
                int delta = 0;
                if (a == v) delta = 1;
                else if (a == k) delta = -1;
                cur = max(0, cur + delta);
                best = max(best, cur);
            }
            bestGain = max(bestGain, best);
        }
        return totalK + bestGain;
    }
};
// @lc code=end
