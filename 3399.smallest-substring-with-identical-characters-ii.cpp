#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3399 lang=cpp
 *
 * [3399] Smallest Substring With Identical Characters II
 */

// @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = (int)s.size();

        auto can = [&](int L) -> bool {
            if (L == 1) {
                // Must be alternating: either 0101... or 1010...
                int diff0 = 0, diff1 = 0;
                for (int i = 0; i < n; i++) {
                    char expect0 = (i % 2 == 0) ? '0' : '1';
                    char expect1 = (i % 2 == 0) ? '1' : '0';
                    if (s[i] != expect0) diff0++;
                    if (s[i] != expect1) diff1++;
                }
                return min(diff0, diff1) <= numOps;
            }

            long long ops = 0;
            for (int i = 0; i < n;) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                int len = j - i;
                // minimal flips to make this run's max block length <= L
                ops += len / (L + 1);
                if (ops > numOps) return false;
                i = j;
            }
            return ops <= numOps;
        };

        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (can(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
// @lc code=end
