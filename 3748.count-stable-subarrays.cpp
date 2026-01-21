#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> endd(n);
        endd[n-1] = n;
        for (int i = n-2; i >= 0; --i) {
            if (nums[i] > nums[i+1]) {
                endd[i] = i;
            } else {
                endd[i] = endd[i+1];
            }
        }
        vector<long long> pref(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i-1] + endd[i-1];
        }
        int q = queries.size();
        vector<long long> result(q);
        for (int qi = 0; qi < q; ++qi) {
            int l = queries[qi][0];
            int r = queries[qi][1];
            auto it = lower_bound(endd.begin() + l, endd.begin() + r + 1, r + 1);
            int split = it - endd.begin();
            int mm = split - 1;
            long long sum1 = 0;
            if (mm >= l) {
                long long num1 = (long long)mm - l + 1;
                long long sumend = pref[mm + 1] - pref[l];
                long long sumni = num1 * ((long long)l + mm) / 2;
                sum1 = sumend - sumni + num1;
            }
            long long num2 = (long long)r - split + 1;
            long long sum2 = 0;
            if (num2 > 0) {
                sum2 = num2 * (num2 + 1) / 2;
            }
            result[qi] = sum1 + sum2;
        }
        return result;
    }
};
# @lc code=end