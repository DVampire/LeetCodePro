#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3605 lang=cpp
//
// [3605] Minimum Stability Factor of Array
//

// @lc code=start
class Solution {
    struct GcdSparseTable {
        int n;
        vector<int> lg;
        vector<vector<int>> st;

        GcdSparseTable() : n(0) {}

        explicit GcdSparseTable(const vector<int>& a) { build(a); }

        void build(const vector<int>& a) {
            n = (int)a.size();
            lg.assign(n + 1, 0);
            for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
            int K = lg[n] + 1;
            st.assign(K, vector<int>(n));
            if (n == 0) return;
            st[0] = a;
            for (int j = 1; j < K; j++) {
                int len = 1 << j;
                int half = len >> 1;
                for (int i = 0; i + len <= n; i++) {
                    st[j][i] = std::gcd(st[j - 1][i], st[j - 1][i + half]);
                }
            }
        }

        int query(int l, int r) const {
            int len = r - l + 1;
            int j = lg[len];
            return std::gcd(st[j][l], st[j][r - (1 << j) + 1]);
        }
    };

public:
    int minStable(vector<int>& nums, int maxC) {
        int n = (int)nums.size();
        GcdSparseTable sp(nums);

        auto feasible = [&](int L) -> bool {
            int K = L + 1;
            if (K > n) return true; // no windows => cannot have stable subarray longer than L

            int used = 0;
            int lastPoint = -1; // last chosen modification index (set to 1)

            for (int i = 0; i + K <= n; i++) {
                if (i <= lastPoint) continue; // current window already stabbed
                int g = sp.query(i, i + K - 1);
                if (g >= 2) {
                    used++;
                    if (used > maxC) return false;
                    lastPoint = i + K - 1; // stab at right endpoint
                }
            }
            return true;
        };

        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
// @lc code=end
