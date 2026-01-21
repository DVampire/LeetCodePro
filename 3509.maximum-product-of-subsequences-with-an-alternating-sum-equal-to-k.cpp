#include <bits/stdc++.h>
using namespace std;

#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = (int)nums.size();
        int maxSum = 12 * n;
        if (k < -maxSum || k > maxSum) return -1;

        int offset = maxSum;
        int range = 2 * maxSum + 1;
        int W = limit / 64 + 1; // number of uint64_t blocks
        size_t SZ = (size_t)range * W;

        vector<uint64_t> dp[2], nxt[2];
        dp[0].assign(SZ, 0); dp[1].assign(SZ, 0);
        nxt[0].assign(SZ, 0); nxt[1].assign(SZ, 0);

        vector<char> activeFlag[2], nextActiveFlag[2];
        activeFlag[0].assign(range, 0); activeFlag[1].assign(range, 0);
        nextActiveFlag[0].assign(range, 0); nextActiveFlag[1].assign(range, 0);

        vector<int> active[2], nextActive[2];

        auto ptrAt = [&](vector<uint64_t>& arr, int sumIdx) -> uint64_t* {
            return arr.data() + (size_t)sumIdx * W;
        };

        auto activateIfNeeded = [&](int p, int sumIdx) {
            if (!nextActiveFlag[p][sumIdx]) {
                nextActiveFlag[p][sumIdx] = 1;
                nextActive[p].push_back(sumIdx);
            }
        };

        auto setBit = [&](uint64_t* bits, int prod) {
            bits[prod >> 6] |= (1ULL << (prod & 63));
        };

        for (int x : nums) {
            // next = dp (skip current element)
            memcpy(nxt[0].data(), dp[0].data(), SZ * sizeof(uint64_t));
            memcpy(nxt[1].data(), dp[1].data(), SZ * sizeof(uint64_t));
            nextActiveFlag[0] = activeFlag[0];
            nextActiveFlag[1] = activeFlag[1];
            nextActive[0] = active[0];
            nextActive[1] = active[1];

            // Start new subsequence with [x]
            if (x <= limit) {
                int sumIdx = offset + x;
                if (0 <= sumIdx && sumIdx < range) {
                    activateIfNeeded(1, sumIdx);
                    uint64_t* dst = ptrAt(nxt[1], sumIdx);
                    setBit(dst, x);
                }
            }

            // Extend existing subsequences
            for (int p = 0; p <= 1; ++p) {
                for (int sumIdx : active[p]) {
                    uint64_t* src = ptrAt(dp[p], sumIdx);

                    int delta = (p == 0 ? x : -x);
                    int dstSum = sumIdx + delta;
                    if (dstSum < 0 || dstSum >= range) continue;
                    int np = 1 - p;

                    if (x == 0) {
                        // product becomes 0
                        activateIfNeeded(np, dstSum);
                        uint64_t* dst = ptrAt(nxt[np], dstSum);
                        setBit(dst, 0);
                        continue;
                    }

                    uint64_t* dst = ptrAt(nxt[np], dstSum);

                    if (x == 1) {
                        // OR whole bitset (product unchanged)
                        activateIfNeeded(np, dstSum);
                        for (int wi = 0; wi < W; ++wi) dst[wi] |= src[wi];
                        continue;
                    }

                    int maxPr = limit / x;
                    bool activated = nextActiveFlag[np][dstSum];

                    for (int wi = 0; wi < W; ++wi) {
                        uint64_t word = src[wi];
                        while (word) {
                            int b = __builtin_ctzll(word);
                            int pr = (wi << 6) + b;
                            word &= (word - 1);
                            if (pr > limit) continue;

                            int newPr;
                            if (pr == 0) newPr = 0;
                            else {
                                if (pr > maxPr) continue;
                                newPr = pr * x;
                            }
                            if (newPr > limit) continue;

                            if (!activated) {
                                activateIfNeeded(np, dstSum);
                                activated = true;
                            }
                            setBit(dst, newPr);
                        }
                    }
                }
            }

            dp[0].swap(nxt[0]);
            dp[1].swap(nxt[1]);
            activeFlag[0].swap(nextActiveFlag[0]);
            activeFlag[1].swap(nextActiveFlag[1]);
            active[0].swap(nextActive[0]);
            active[1].swap(nextActive[1]);
        }

        int targetIdx = offset + k;
        if (targetIdx < 0 || targetIdx >= range) return -1;

        auto getMaxProduct = [&](vector<uint64_t>& arr) -> int {
            uint64_t* bits = ptrAt(arr, targetIdx);
            int lastBits = (limit & 63);
            uint64_t lastMask = (lastBits == 63) ? ~0ULL : ((1ULL << (lastBits + 1)) - 1ULL);

            for (int wi = W - 1; wi >= 0; --wi) {
                uint64_t word = bits[wi];
                if (wi == W - 1) word &= lastMask;
                if (!word) continue;
                int msb = 63 - __builtin_clzll(word);
                int prod = (wi << 6) + msb;
                if (prod <= limit) return prod;
            }
            return -1;
        };

        int a = getMaxProduct(dp[0]);
        int b = getMaxProduct(dp[1]);
        return max(a, b);
    }
};
# @lc code=end
