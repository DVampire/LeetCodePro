//
// @lc app=leetcode id=3768 lang=cpp
//
// [3768] Minimum Inversion Count in Subarrays of Fixed Length
//

// @lc code=start
class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Coordinate compression
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());
        sortedNums.erase(unique(sortedNums.begin(), sortedNums.end()), sortedNums.end());
        unordered_map<int, int> compress;
        for (int i = 0; i < (int)sortedNums.size(); i++) {
            compress[sortedNums[i]] = i + 1;
        }
        
        int m = sortedNums.size();
        vector<int> bit(m + 1, 0);
        
        auto update = [&](int i, int delta) {
            for (; i <= m; i += i & (-i))
                bit[i] += delta;
        };
        
        auto query = [&](int i) -> int {
            int sum = 0;
            for (; i > 0; i -= i & (-i))
                sum += bit[i];
            return sum;
        };
        
        // Count inversions in the first window
        long long inv = 0;
        for (int i = 0; i < k; i++) {
            int ci = compress[nums[i]];
            // Count elements > nums[i] that have been added
            inv += i - query(ci);
            update(ci, 1);
        }
        
        long long result = inv;
        
        // Slide the window
        for (int l = 1; l + k - 1 < n; l++) {
            int leftVal = compress[nums[l - 1]];
            int rightVal = compress[nums[l + k - 1]];
            
            // Remove nums[l-1] from BIT
            update(leftVal, -1);
            
            // Lost inversions: elements < nums[l-1] in the remaining window
            inv -= query(leftVal - 1);
            
            // Gained inversions: elements > nums[l+k-1] in the current window
            inv += (k - 1) - query(rightVal);
            
            // Add nums[l+k-1] to BIT
            update(rightVal, 1);
            
            result = min(result, inv);
        }
        
        return result;
    }
};
// @lc code=end