#include <iostream>

#
# @lc app=leetcode id=3677 lang=cpp
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;

        int bitLen = 0;
        long long tempN = n;
        while (tempN > 0) {
            tempN >>= 1;
            bitLen++;
        }

        long long totalCount = 1; // Account for the number 0 ("0")

        // Count palindromes with length L < bitLen
        for (int L = 1; L < bitLen; ++L) {
            int halfLen = (L + 1) / 2;
            totalCount += (1LL << (halfLen - 1));
        }

        // Count palindromes with length L = bitLen
        int L = bitLen;
        int halfLen = (L + 1) / 2;
        long long firstHalfOfN = n >> (L - halfLen);

        // Number of first halves X such that 2^(halfLen-1) <= X < firstHalfOfN
        totalCount += (firstHalfOfN - (1LL << (halfLen - 1)));

        // Construct the palindrome from firstHalfOfN and check if it's <= n
        long long pal = firstHalfOfN;
        long long temp = (L % 2 == 0) ? firstHalfOfN : (firstHalfOfN >> 1);
        for (int i = 0; i < L / 2; ++i) {
            pal = (pal << 1) | (temp & 1);
            temp >>= 1;
        }

        if (pal <= n) {
            totalCount++;
        }

        return (int)totalCount;
    }
};
# @lc code=end