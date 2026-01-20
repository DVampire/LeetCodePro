#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#

# @lc code=start
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        // B stores indices i such that nums[i] > nums[i+1]
        // These are the split points where stable segments break.
        vector<int> B;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] > nums[i+1]) {
                B.push_back(i);
            }
        }

        int m = B.size();
        // P stores prefix sums of squared lengths of full segments ending at B[i].
        // The segment corresponding to B[i] spans from B[i-1] + 1 to B[i].
        vector<long long> P(m);
        for (int i = 0; i < m; ++i) {
            long long prev_b = (i == 0) ? -1 : B[i-1];
            long long len = B[i] - prev_b;
            long long sq = len * len;
            P[i] = (i == 0) ? sq : (P[i-1] + sq);
        }

        vector<long long> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int L = q[0];
            int R = q[1];
            
            // Find first bad index >= L. This is the first split inside [L, R].
            auto it_L = lower_bound(B.begin(), B.end(), L);
            int idx_L = distance(B.begin(), it_L);

            // Find last bad index < R. This is the last split inside [L, R].
            // We search for R and go back one step.
            auto it_R_bound = lower_bound(B.begin(), B.end(), R);
            int idx_R = distance(B.begin(), it_R_bound) - 1;

            // If no split points in [L, R-1], the whole range is stable.
            if (idx_L > idx_R) {
                long long len = R - L + 1;
                ans.push_back(len * (len + 1) / 2);
            } else {
                // Calculate sum of squares of lengths of stable pieces.
                // 1. Left piece: [L, B[idx_L]]
                long long left_len = B[idx_L] - L + 1;
                
                // 2. Right piece: [B[idx_R] + 1, R]
                long long right_len = R - B[idx_R];
                
                // 3. Middle pieces: Defined by bad indices from idx_L + 1 to idx_R.
                // Their squared lengths are stored in P.
                long long mid_sq_sum = 0;
                if (idx_R > idx_L) {
                    mid_sq_sum = P[idx_R] - P[idx_L];
                }

                long long total_sq = left_len * left_len + right_len * right_len + mid_sq_sum;
                long long total_len = R - L + 1;
                
                // Sum 1..k = k(k+1)/2 = (k^2 + k)/2
                // Sum over all segments = (Sum(len^2) + Sum(len)) / 2
                ans.push_back((total_sq + total_len) / 2);
            }
        }
        return ans;
    }
};
# @lc code=end