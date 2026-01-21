#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#
# @lc code=start
class Solution {
public:
    class BIT {
        vector<int> tree;
        int n;
    public:
        BIT(int n) : n(n), tree(n + 1, 0) {}
        
        void update(int idx, int delta) {
            for (int i = idx; i <= n; i += i & -i) {
                tree[i] += delta;
            }
        }
        
        int query(int idx) {
            if (idx <= 0) return 0;
            int sum = 0;
            for (int i = idx; i > 0; i -= i & -i) {
                sum += tree[i];
            }
            return sum;
        }
    };
    
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Coordinate compression
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
        
        map<int, int> compress;
        for (int i = 0; i < sorted_nums.size(); i++) {
            compress[sorted_nums[i]] = i + 1;
        }
        
        int m = sorted_nums.size();
        BIT bit(m);
        
        // Count inversions for first window
        long long currentInversions = 0;
        for (int i = 0; i < k; i++) {
            int compressed = compress[nums[i]];
            currentInversions += bit.query(m) - bit.query(compressed);
            bit.update(compressed, 1);
        }
        
        long long minInversions = currentInversions;
        
        // Slide the window
        for (int i = k; i < n; i++) {
            int removed = nums[i - k];
            int removedCompressed = compress[removed];
            int smallerCount = bit.query(removedCompressed - 1);
            currentInversions -= smallerCount;
            bit.update(removedCompressed, -1);
            
            int added = nums[i];
            int addedCompressed = compress[added];
            int greaterCount = bit.query(m) - bit.query(addedCompressed);
            currentInversions += greaterCount;
            bit.update(addedCompressed, 1);
            
            minInversions = min(minInversions, currentInversions);
        }
        
        return minInversions;
    }
};
# @lc code=end