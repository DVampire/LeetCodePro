#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
#include <vector>
#include <iostream>

class Solution {
public:
    long long nCr[66][66];
    int depth[66];

    void precompute() {
        for (int i = 0; i <= 65; i++) {
            nCr[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
            }
        }

        depth[1] = 0;
        for (int i = 2; i <= 65; i++) {
            depth[i] = 1 + depth[__builtin_popcount(i)];
        }
    }

    long long countWithPopcount(long long n, int target_c) {
        if (target_c < 0 || target_c > 64) return 0;
        long long count = 0;
        int current_c = 0;
        for (int i = 62; i >= 0; i--) {
            if ((n >> i) & 1) {
                int needed = target_c - current_c;
                if (needed >= 0 && needed <= i) {
                    count += nCr[i][needed];
                }
                current_c++;
            }
        }
        if (current_c == target_c) count++;
        return count;
    }

    long long popcountDepth(long long n, int k) {
        if (k == 0) return 1; // Only x = 1
        precompute();

        long long total = 0;
        for (int c = 1; c <= 64; c++) {
            if (depth[c] == k - 1) {
                total += countWithPopcount(n, c);
            }
        }

        // If k=1, we counted x=1 (popcount 1, depth 0) but we need depth 1.
        if (k == 1) {
            total--;
        }

        return total;
    }
};
# @lc code=end