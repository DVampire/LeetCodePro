#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        vector<long long> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + nums[i - 1];
        }
        const long long INF = LLONG_MAX / 2;
        const long long NINF = LLONG_MIN / 2;

        // Left increasing for p
        vector<int> L(n);
        vector<long long> gmin(n, INF);
        L[0] = 0;
        gmin[0] = INF;
        for (int p = 1; p < n; ++p) {
            if (nums[p] > nums[p - 1]) {
                L[p] = L[p - 1];
                gmin[p] = min(gmin[p - 1], pre[p - 1]);
            } else {
                L[p] = p;
                gmin[p] = INF;
            }
        }

        // Right increasing for q
        vector<int> R(n);
        vector<long long> fmax(n, NINF);
        R[n - 1] = n - 1;
        fmax[n - 1] = NINF;
        for (int q = n - 2; q >= 0; --q) {
            if (nums[q + 1] > nums[q]) {
                R[q] = R[q + 1];
                fmax[q] = max(pre[q + 2], fmax[q + 1]);
            } else {
                R[q] = q;
                fmax[q] = NINF;
            }
        }

        // Dec left for q
        vector<int> D(n);
        D[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                D[i] = D[i - 1];
            } else {
                D[i] = i;
            }
        }

        // Sparse table for min on gmin
        int LOG = 0;
        while ((1 << LOG) <= n) ++LOG;
        vector<vector<long long>> st(LOG, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            st[0][i] = gmin[i];
        }
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
        vector<int> logg(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            logg[i] = logg[i / 2] + 1;
        }

        auto query = [&](int le, int ri) -> long long {
            if (le > ri) return INF;
            int len = ri - le + 1;
            int k = logg[len];
            return min(st[k][le], st[k][ri - (1 << k) + 1]);
        };

        long long ans = NINF;
        for (int q = 0; q < n; ++q) {
            if (fmax[q] == NINF) continue;
            int dl = D[q];
            if (dl >= q) continue;
            long long min_g = query(dl, q - 1);
            if (min_g == INF) continue;
            long long cursum = fmax[q] - min_g;
            ans = max(ans, cursum);
        }
        return ans;
    }
};
# @lc code=end