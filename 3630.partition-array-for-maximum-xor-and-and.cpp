#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3630 lang=cpp
//
// [3630] Partition Array for Maximum XOR and AND
//

// @lc code=start
class Solution {
public:
    long long maximizeXorAndXor(vector<int>& nums) {
        int n = (int)nums.size();
        int full = 1 << n;

        // nums[i] <= 1e9 < 2^30
        const int BITS = 30;
        const int ALL = (1 << BITS) - 1;

        vector<int> xr(full, 0);
        vector<int> andv(full, 0);
        andv[0] = ALL; // identity for AND when building; empty handled separately later

        for (int mask = 1; mask < full; ++mask) {
            int lsb = mask & -mask;
            int i = __builtin_ctz(lsb);
            int pm = mask ^ lsb;
            xr[mask] = xr[pm] ^ nums[i];
            andv[mask] = andv[pm] & nums[i];
        }

        auto insertBasis = [&](int x, array<int, BITS>& basis) {
            for (int b = BITS - 1; b >= 0 && x; --b) {
                if (((x >> b) & 1) == 0) continue;
                if (basis[b] == 0) {
                    basis[b] = x;
                    return;
                }
                x ^= basis[b];
            }
        };

        auto maxSubsetXor = [&](const array<int, BITS>& basis) {
            int res = 0;
            for (int b = BITS - 1; b >= 0; --b) {
                if (basis[b] == 0) continue;
                res = max(res, res ^ basis[b]);
            }
            return res;
        };

        long long ans = 0;
        int allMask = full - 1;

        for (int B = 0; B < full; ++B) {
            int R = allMask ^ B;

            int X = xr[R];
            int M = ALL ^ X; // ~X within 30 bits

            array<int, BITS> basis{};
            int tmp = R;
            while (tmp) {
                int lsb = tmp & -tmp;
                int i = __builtin_ctz(lsb);
                tmp ^= lsb;
                int v = nums[i] & M;
                insertBasis(v, basis);
            }
            int mx = maxSubsetXor(basis);
            long long bestXorSum = (long long)X + 2LL * (long long)mx;

            long long andB = (B == 0 ? 0LL : (long long)andv[B]);
            ans = max(ans, bestXorSum + andB);
        }

        return ans;
    }
};
// @lc code=end
