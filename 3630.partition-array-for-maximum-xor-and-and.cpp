#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#
# @lc app=leetcode id=3630 lang=cpp
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution {
    long long max_val = 0;
    int n;

    struct Basis {
        int v[31];
        Basis() { memset(v, 0, sizeof(v)); }
        
        void insert(int x) {
            for (int i = 30; i >= 0; --i) {
                if (!(x & (1 << i))) continue;
                if (!v[i]) {
                    v[i] = x;
                    return;
                }
                x ^= v[i];
            }
        }
    };

    void backtrack(int idx, int xor_s, int and_b, bool b_empty, const vector<int>& nums, Basis basis) {
        if (idx == n) {
            int mask = ~xor_s;
            Basis masked_basis;
            for (int i = 0; i <= 30; ++i) {
                if (basis.v[i]) {
                    masked_basis.insert(basis.v[i] & mask);
                }
            }
            
            int max_x_and_mask = 0;
            for (int i = 30; i >= 0; --i) {
                if (!(max_x_and_mask & (1 << i)) && masked_basis.v[i]) {
                    max_x_and_mask ^= masked_basis.v[i];
                }
            }
            
            long long current_and = b_empty ? 0 : and_b;
            long long current_total = current_and + (long long)xor_s + 2LL * max_x_and_mask;
            if (current_total > max_val) max_val = current_total;
            return;
        }

        // Option 1: nums[idx] goes to B
        backtrack(idx + 1, xor_s, b_empty ? nums[idx] : (and_b & nums[idx]), false, nums, basis);

        // Option 2: nums[idx] goes to S
        basis.insert(nums[idx]);
        backtrack(idx + 1, xor_s ^ nums[idx], and_b, b_empty, nums, basis);
    }

public:
    long long maximizeXorAndXor(vector<int>& nums) {
        n = nums.size();
        max_val = 0;
        Basis initial_basis;
        backtrack(0, 0, 0, true, nums, initial_basis);
        return max_val;
    }
};
# @lc code=end