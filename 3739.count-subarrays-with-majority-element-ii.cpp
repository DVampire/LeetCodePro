#
# @lc app=leetcode id=3739 lang=cpp
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // The prefix sum range is [-n, n]. We map this to [1, 2n+1] using an offset.
        int size = 2 * n + 1;
        int offset = n + 1;
        vector<int> bit(size + 1, 0);

        auto update = [&](int idx, int val) {
            for (; idx <= size; idx += idx & -idx)
                bit[idx] += val;
        };

        auto query = [&](int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res += bit[idx];
            return res;
        };

        long long totalCount = 0;
        int currentPrefixSum = 0;
        
        // Initial prefix sum S_0 = 0
        update(currentPrefixSum + offset, 1);

        for (int num : nums) {
            if (num == target) {
                currentPrefixSum += 1;
            } else {
                currentPrefixSum -= 1;
            }
            
            // We need to count S_i such that S_i < currentPrefixSum.
            // This corresponds to indices in BIT from 1 to (currentPrefixSum + offset - 1).
            totalCount += query(currentPrefixSum + offset - 1);
            
            // Add current prefix sum to BIT.
            update(currentPrefixSum + offset, 1);
        }

        return totalCount;
    }
};
# @lc code=end