#
# @lc app=leetcode id=3739 lang=cpp
#
# [3739] Count Subarrays With Majority Element II
#
# @lc code=start
class Solution {
public:
    class BIT {
    public:
        vector<int> tree;
        int n;
        
        BIT(int n) : n(n), tree(n + 1, 0) {}
        
        void update(int idx, int delta) {
            for (++idx; idx <= n; idx += idx & -idx) {
                tree[idx] += delta;
            }
        }
        
        int query(int idx) {
            int sum = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                sum += tree[idx];
            }
            return sum;
        }
    };
    
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        
        // Compute prefix sums with transformation
        vector<int> prefix(n + 1);
        prefix[0] = 0;
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + (nums[i] == target ? 1 : -1);
        }
        
        // Coordinate compression
        vector<int> sorted_prefix = prefix;
        sort(sorted_prefix.begin(), sorted_prefix.end());
        sorted_prefix.erase(unique(sorted_prefix.begin(), sorted_prefix.end()), sorted_prefix.end());
        
        auto get_compressed = [&](int val) {
            return lower_bound(sorted_prefix.begin(), sorted_prefix.end(), val) - sorted_prefix.begin();
        };
        
        int m = sorted_prefix.size();
        BIT bit(m);
        
        long long count = 0;
        
        // Add prefix[0] to BIT
        bit.update(get_compressed(prefix[0]), 1);
        
        for (int r = 0; r < n; r++) {
            int compressed = get_compressed(prefix[r + 1]);
            
            // Count how many prefix sums are < prefix[r+1]
            if (compressed > 0) {
                count += bit.query(compressed - 1);
            }
            
            // Add prefix[r+1] to BIT
            bit.update(compressed, 1);
        }
        
        return count;
    }
};
# @lc code=end