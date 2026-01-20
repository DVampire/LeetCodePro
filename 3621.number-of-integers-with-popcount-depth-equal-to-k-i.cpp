#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
#include <vector>

class Solution {
    long long nCr[66][66];

    void precomputeNCR() {
        for (int i = 0; i <= 65; i++) {
            nCr[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
            }
        }
    }

    long long countWithPopcount(long long n, int target) {
        if (target < 0) return 0;
        long long count = 0;
        int current_popcount = 0;
        for (int i = 62; i >= 0; --i) {
            if ((n >> i) & 1) {
                if (target - current_popcount >= 0 && target - current_popcount <= i) {
                    count += nCr[i][target - current_popcount];
                }
                current_popcount++;
            }
        }
        if (current_popcount == target) {
            count++;
        }
        return count;
    }

public:
    long long popcountDepth(long long n, int k) {
        if (k == 0) return 1;

        precomputeNCR();

        int d_vals[66];
        d_vals[1] = 0;
        for (int i = 2; i <= 64; ++i) {
            int pc = 0;
            int temp = i;
            while (temp > 0) {
                if (temp & 1) pc++;
                temp >>= 1;
            }
            d_vals[i] = 1 + d_vals[pc];
        }

        long long total = 0;
        for (int c = 1; c <= 64; ++c) {
            if (d_vals[c] == k - 1) {
                total += countWithPopcount(n, c);
            }
        }

        if (k == 1) {
            total--; // exclude x=1, which has popcount 1 but depth 0
        }

        return total;
    }
};
# @lc code=end