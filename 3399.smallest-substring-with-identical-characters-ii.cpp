#include <bits/stdc++.h>
using namespace std;

//
// @lc app=leetcode id=3399 lang=cpp
//
// [3399] Smallest Substring With Identical Characters II
//

// @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = (int)s.size();

        // Precompute run lengths
        vector<int> runs;
        runs.reserve(n);
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            runs.push_back(j - i);
            i = j;
        }

        // Precompute cost to make alternating (for L == 1)
        int cost0101 = 0, cost1010 = 0;
        for (int i = 0; i < n; ++i) {
            char e0 = (i % 2 == 0) ? '0' : '1';
            char e1 = (i % 2 == 0) ? '1' : '0';
            if (s[i] != e0) ++cost0101;
            if (s[i] != e1) ++cost1010;
        }
        int altCost = min(cost0101, cost1010);

        auto neededOps = [&](int L) -> long long {
            if (L == 1) return altCost;
            long long ops = 0;
            int div = L + 1;
            for (int r : runs) {
                ops += r / div;
                if (ops > numOps) return ops; // early stop
            }
            return ops;
        };

        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (neededOps(mid) <= numOps) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
// @lc code=end
