#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    // Fenwick Tree (Binary Indexed Tree) implementation
    vector<int> bit;
    int size;

    void update(int idx, int val) {
        for (; idx <= size; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += bit[idx];
        }
        return sum;
    }

public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Coordinate Compression
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        // Remove duplicates for unique ranking
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
        
        auto get_rank = [&](int val) {
            return lower_bound(sorted_nums.begin(), sorted_nums.end(), val) - sorted_nums.begin() + 1;
        };
        
        // Initialize BIT
        size = sorted_nums.size();
        bit.assign(size + 1, 0);
        
        long long current_inversions = 0;
        
        // Process the first window
        for (int i = 0; i < k; ++i) {
            int r = get_rank(nums[i]);
            // Count elements currently in the window (processed so far) that are greater than nums[i]
            // Total processed so far is i. Elements <= nums[i] is query(r).
            // Elements > nums[i] is i - query(r).
            current_inversions += (i - query(r));
            update(r, 1);
        }
        
        long long min_inversions = current_inversions;
        
        // Slide the window
        for (int i = 0; i < n - k; ++i) {
            // Remove nums[i] (the element leaving the window from the left)
            int leaving_rank = get_rank(nums[i]);
            
            // Before removing, we need to subtract inversions caused by nums[i].
            // Since nums[i] was at the left, it formed inversions with all elements 
            // currently in the window (excluding itself) that are smaller than it.
            // We remove it from BIT first to query the remaining elements easily.
            update(leaving_rank, -1);
            
            // Now BIT contains elements from nums[i+1...i+k-1]
            // Count how many are smaller than nums[i]
            long long smaller_than_leaving = query(leaving_rank - 1);
            current_inversions -= smaller_than_leaving;
            
            // Add nums[i+k] (the element entering the window from the right)
            int entering_rank = get_rank(nums[i+k]);
            
            // It forms inversions with all elements currently in the window that are larger than it.
            // BIT currently contains elements from nums[i+1...i+k-1], size is k-1.
            // Count how many are larger than nums[i+k]
            long long larger_than_entering = (k - 1) - query(entering_rank);
            current_inversions += larger_than_entering;
            
            update(entering_rank, 1);
            
            min_inversions = min(min_inversions, current_inversions);
        }
        
        return min_inversions;
    }
};
# @lc code=end