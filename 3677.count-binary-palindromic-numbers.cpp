#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
    static long long makePal(long long x, int len) {
        long long res = x;
        long long y = x;
        if (len & 1) y >>= 1; // drop the middle bit for odd length
        while (y > 0) {
            res = (res << 1) | (y & 1);
            y >>= 1;
        }
        return res;
    }

public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1; // only "0"

        int L = 64 - __builtin_clzll((unsigned long long)n); // bit length of n
        long long total = 0;

        // Count all palindromes with length < L
        total += 2; // len=1: {0,1}
        for (int len = 2; len <= L - 1; ++len) {
            int halfLen = (len + 1) / 2;
            total += 1LL << (halfLen - 1);
        }

        // Count palindromes of length == L and <= n
        if (L == 1) {
            // n >= 1 here, so {0,1}
            return 2;
        }
        int halfLen = (L + 1) / 2;
        long long base = 1LL << (halfLen - 1);
        long long prefix = n >> (L - halfLen);

        long long cnt = prefix - base;
        long long cand = makePal(prefix, L);
        if (cand <= n) cnt++;

        total += cnt;
        return (int)total;
    }
};
// @lc code=end
