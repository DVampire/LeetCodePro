#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3569 lang=cpp
 *
 * [3569] Maximize Count of Distinct Primes After Split
 */

// @lc code=start
class Solution {
    struct SegTree {
        int n;
        vector<int> mx, lazy;
        SegTree(int n_=0) { init(n_); }
        void init(int n_) {
            n = n_;
            mx.assign(4 * max(1, n), 0);
            lazy.assign(4 * max(1, n), 0);
        }
        void push(int node) {
            if (lazy[node] != 0) {
                int v = lazy[node];
                for (int ch : {node * 2, node * 2 + 1}) {
                    mx[ch] += v;
                    lazy[ch] += v;
                }
                lazy[node] = 0;
            }
        }
        void add(int node, int l, int r, int ql, int qr, int val) {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                mx[node] += val;
                lazy[node] += val;
                return;
            }
            push(node);
            int mid = (l + r) >> 1;
            add(node * 2, l, mid, ql, qr, val);
            add(node * 2 + 1, mid + 1, r, ql, qr, val);
            mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
        }
        void rangeAdd(int l, int r, int val) {
            if (n <= 0 || l > r) return;
            l = max(l, 1);
            r = min(r, n);
            if (l > r) return;
            add(1, 1, n, l, r, val);
        }
        int queryMax() const {
            if (n <= 0) return 0;
            return mx[1];
        }
    };

public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        const int MAXV = 100000;

        // Sieve
        vector<bool> isPrime(MAXV + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; 1LL * i * i <= MAXV; i++) {
            if (!isPrime[i]) continue;
            for (int j = i * i; j <= MAXV; j += i) isPrime[j] = false;
        }
        vector<int> primes;
        for (int i = 2; i <= MAXV; i++) if (isPrime[i]) primes.push_back(i);

        int n = (int)nums.size();
        int m = n - 1; // split points k in [1, n-1]
        SegTree seg(m);

        // Occurrence sets for prime values
        vector<set<int>> occ(MAXV + 1);
        for (int i = 0; i < n; i++) {
            int v = nums[i];
            if (v <= MAXV && isPrime[v]) occ[v].insert(i);
        }

        vector<int> L(MAXV + 1, -1), R(MAXV + 1, -1); // active interval per prime

        auto removeInterval = [&](int p) {
            if (L[p] != -1) {
                seg.rangeAdd(L[p], R[p], -1);
                L[p] = R[p] = -1;
            }
        };
        auto addIntervalFromOcc = [&](int p) {
            if ((int)occ[p].size() >= 2) {
                int mn = *occ[p].begin();
                int mx = *occ[p].rbegin();
                int l = mn + 1;
                int r = mx;
                if (l <= r) {
                    L[p] = l;
                    R[p] = r;
                    seg.rangeAdd(l, r, +1);
                }
            }
        };

        int P = 0;
        for (int p : primes) {
            if (!occ[p].empty()) P++;
            addIntervalFromOcc(p);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &qu : queries) {
            int idx = qu[0];
            int val = qu[1];
            int old = nums[idx];

            if (old != val) {
                // Remove old value
                if (old <= MAXV && isPrime[old]) {
                    removeInterval(old);
                    int before = (int)occ[old].size();
                    occ[old].erase(idx);
                    int after = (int)occ[old].size();
                    if (before > 0 && after == 0) P--;
                    addIntervalFromOcc(old);
                }

                // Add new value
                if (val <= MAXV && isPrime[val]) {
                    removeInterval(val);
                    int before = (int)occ[val].size();
                    occ[val].insert(idx);
                    int after = (int)occ[val].size();
                    if (before == 0 && after > 0) P++;
                    addIntervalFromOcc(val);
                }

                nums[idx] = val;
            }

            ans.push_back(P + seg.queryMax());
        }

        return ans;
    }
};
// @lc code=end
