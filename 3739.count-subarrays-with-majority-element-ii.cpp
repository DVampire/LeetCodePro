//
// @lc app=leetcode id=3739 lang=cpp
//
// [3739] Count Subarrays With Majority Element II
//
// @lc code=start
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int offset = n + 1;
        int size = 2 * n + 3;
        vector<long long> bit(size, 0);
        
        auto update = [&](int idx) {
            for (; idx < size; idx += idx & (-idx))
                bit[idx]++;
        };
        
        auto query = [&](int idx) -> long long {
            long long sum = 0;
            for (; idx > 0; idx -= idx & (-idx))
                sum += bit[idx];
            return sum;
        };
        
        long long result = 0;
        int prefix = 0;
        
        // Add initial prefix value (0) to BIT
        update(prefix + offset);
        
        for (int i = 0; i < n; i++) {
            prefix += (nums[i] == target) ? 1 : -1;
            // Count how many previous prefix values are strictly less than current prefix
            int queryIdx = prefix + offset - 1;
            if (queryIdx >= 1) {
                result += query(queryIdx);
            }
            update(prefix + offset);
        }
        
        return result;
    }
};
// @lc code=end