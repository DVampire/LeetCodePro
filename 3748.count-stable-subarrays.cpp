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
        
        // Assign segment id to each position
        // A new segment starts when nums[i] < nums[i-1] (non-decreasing segments)
        vector<int> seg_id(n);
        seg_id[0] = 0;
        for (int i = 1; i < n; i++) {
            seg_id[i] = seg_id[i-1] + (nums[i] < nums[i-1] ? 1 : 0);
        }
        
        int m = seg_id[n-1] + 1;  // Number of segments
        
        // Find segment boundaries
        vector<int> seg_start(m), seg_end(m);
        for (int i = 0; i < n; i++) {
            int s = seg_id[i];
            if (i == 0 || seg_id[i] != seg_id[i-1]) {
                seg_start[s] = i;
            }
            seg_end[s] = i;
        }
        
        // Compute prefix contributions
        // For a segment of length len, number of subarrays = len*(len+1)/2
        vector<long long> prefix_contrib(m + 1, 0);
        for (int j = 0; j < m; j++) {
            long long len = seg_end[j] - seg_start[j] + 1;
            prefix_contrib[j + 1] = prefix_contrib[j] + len * (len + 1) / 2;
        }
        
        // Process queries
        vector<long long> ans;
        ans.reserve(queries.size());
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int a = seg_id[l], b = seg_id[r];
            
            if (a == b) {
                // l and r are in the same segment
                long long len = r - l + 1;
                ans.push_back(len * (len + 1) / 2);
            } else {
                // Different segments
                // Partial contribution from segment a (from l to seg_end[a])
                long long len_a = seg_end[a] - l + 1;
                // Partial contribution from segment b (from seg_start[b] to r)
                long long len_b = r - seg_start[b] + 1;
                // Full contributions from segments a+1 to b-1
                long long result = len_a * (len_a + 1) / 2;
                result += prefix_contrib[b] - prefix_contrib[a + 1];
                result += len_b * (len_b + 1) / 2;
                ans.push_back(result);
            }
        }
        
        return ans;
    }
};
# @lc code=end