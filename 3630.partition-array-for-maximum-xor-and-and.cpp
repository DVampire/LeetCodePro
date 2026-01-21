#
# @lc app=leetcode id=3630 lang=cpp
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximizeXorAndXor(vector<int>& nums) {
        int n = nums.size();
        long long total_xor = 0;
        for (int x : nums) total_xor ^= x;
        long long ans = 0;
        int full = (1 << n) - 1;
        const long long LOW_MASK = (1LL << 32) - 1;
        for (int maskB = 0; maskB <= full; ++maskB) {
            long long xorB = 0;
            long long andB = ~0LL;
            bool b_empty = true;
            for (int i = 0; i < n; ++i) {
                if (maskB & (1 << i)) {
                    b_empty = false;
                    xorB ^= nums[i];
                    andB &= nums[i];
                }
            }
            if (b_empty) andB = 0;
            long long Z = total_xor ^ xorB;
            long long M = (~Z) & LOW_MASK;
            // Build basis for R
            vector<long long> basis(32, 0);
            int maskR = full ^ maskB;
            for (int i = 0; i < n; ++i) {
                if ((maskR & (1 << i)) == 0) continue;
                long long val = nums[i];
                for (int j = 31; j >= 0; --j) {
                    if ((val & (1LL << j)) == 0) continue;
                    if (basis[j] != 0) {
                        val ^= basis[j];
                    } else {
                        basis[j] = val;
                        break;
                    }
                }
            }
            // Query max x & M
            long long max_and = 0;
            for (int j = 31; j >= 0; --j) {
                if ((M & (1LL << j)) && basis[j] != 0 && (max_and & (1LL << j)) == 0) {
                    max_and ^= basis[j];
                }
            }
            long long comp = max_and & M;
            long long max_ac = Z + 2LL * comp;
            long long current = max_ac + andB;
            if (current > ans) ans = current;
        }
        return ans;
    }
};
# @lc code=end