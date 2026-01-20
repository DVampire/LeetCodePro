#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        if (n == 0) return {};

        // g[i] is the smallest index such that nums[g[i]...i] is non-decreasing
        vector<int> g(n);
        g[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] >= nums[i - 1]) {
                g[i] = g[i - 1];
            } else {
                g[i] = i;
            }
        }

        // Prefix sums of g to answer range sum queries on g
        vector<long long> prefG(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefG[i + 1] = prefG[i] + (long long)g[i];
        }

        int q = queries.size();
        vector<long long> ans(q);
        for (int i = 0; i < q; ++i) {
            int L = queries[i][0];
            int R = queries[i][1];

            // Since g is non-decreasing, find the largest k in [L, R] such that g[k] <= L
            // This is equivalent to finding the first index > L and subtracting 1
            auto it = upper_bound(g.begin() + L, g.begin() + R + 1, L);
            int k = (int)(it - g.begin()) - 1;

            // Total = sum_{j=L}^R (j - max(L, g[j]) + 1)
            // Total = sum_{j=L}^R (j + 1) - sum_{j=L}^R max(L, g[j])
            
            // S1 = sum_{j=L}^R (j + 1)
            long long num_terms = (long long)R - L + 1;
            long long S1 = num_terms * (L + R + 2) / 2;

            // S2 = sum_{j=L}^R max(L, g[j])
            // For j in [L, k], g[j] <= L, so max(L, g[j]) = L
            // For j in [k+1, R], g[j] > L, so max(L, g[j]) = g[j]
            long long S2 = (long long)(k - L + 1) * L + (prefG[R + 1] - prefG[k + 1]);

            ans[i] = S1 - S2;
        }

        return ans;
    }
};
# @lc code=end