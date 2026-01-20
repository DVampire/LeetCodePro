#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
    vector<int> tree;
    int size;
public:
    FenwickTree(int n) : size(n), tree(n + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= size; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
};

class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        if (k <= 1) return 0;

        // Coordinate Compression
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());

        auto get_idx = [&](int val) {
            return lower_bound(sorted_nums.begin(), sorted_nums.end(), val) - sorted_nums.begin() + 1;
        };

        vector<int> compressed_nums(n);
        for (int i = 0; i < n; ++i) {
            compressed_nums[i] = get_idx(nums[i]);
        }

        FenwickTree bit(sorted_nums.size());
        long long current_inv = 0;

        // Process initial window of size k
        for (int i = 0; i < k; ++i) {
            int val = compressed_nums[i];
            // Count elements already in BIT that are strictly greater than val
            current_inv += (i - bit.query(val));
            bit.update(val, 1);
        }

        long long min_inv = current_inv;

        // Slide window
        for (int i = 0; i < n - k; ++i) {
            // Remove nums[i]
            int to_remove = compressed_nums[i];
            // Elements in nums[i+1...i+k-1] smaller than nums[i]
            int count_smaller = bit.query(to_remove - 1);
            current_inv -= count_smaller;
            bit.update(to_remove, -1);

            // Add nums[i+k]
            int to_add = compressed_nums[i + k];
            // Elements in nums[i+1...i+k-1] larger than nums[i+k]
            // current BIT size is k-1
            int count_larger = (k - 1) - bit.query(to_add);
            current_inv += count_larger;
            bit.update(to_add, 1);

            if (current_inv < min_inv) {
                min_inv = current_inv;
            }
        }

        return min_inv;
    }
};
# @lc code=end