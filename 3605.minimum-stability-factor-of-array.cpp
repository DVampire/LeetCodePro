#
# @lc app=leetcode id=3605 lang=cpp
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> logg(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            logg[i] = logg[i / 2] + 1;
        }
        const int LOG = 18;
        vector<vector<int>> st(LOG, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            st[0][i] = nums[i];
        }
        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = gcd(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
        auto query = [&](int l, int r) -> int {
            int len = r - l + 1;
            int k = logg[len];
            return gcd(st[k][l], st[k][r - (1 << k) + 1]);
        };
        int low = 0, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            int LEN = mid + 1;
            int count = 0;
            int last = -1;
            for (int r = LEN - 1; r < n; ++r) {
                int l = r - LEN + 1;
                int g = (LEN > n) ? 1 : query(l, r);
                if (g >= 2 && last < l) {
                    last = r;
                    ++count;
                }
            }
            if (count <= maxC) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
# @lc code=end