#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
class Solution {
public:
    struct Fenwick {
        vector<long long> tree;
        int sz;
        Fenwick(int n) : sz(n), tree(n + 2, 0) {}
        void update(int idx, long long val) {
            while (idx <= sz) {
                tree[idx] += val;
                idx += idx & -idx;
            }
        }
        long long query(int idx) {
            long long sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }
        long long query(int l, int r) {
            if (l > r) return 0;
            return query(r) - query(l - 1);
        }
    };

    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = vals.size();
        vector<int> rnk(n);
        for (int i = 0; i < n; i++) {
            rnk[i] = lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin() + 1;
        }
        Fenwick ft(m);
        long long inv = 0;
        // Build first window [0, k-1]
        for (int i = 0; i < k; i++) {
            int rk = rnk[i];
            inv += ft.query(rk + 1, m);
            ft.update(rk, 1);
        }
        long long ans = inv;
        // Slide the window
        for (int start = 1; start <= n - k; start++) {
            int rem_idx = start - 1;
            int rk_rem = rnk[rem_idx];
            long long smaller = ft.query(1, rk_rem - 1);
            inv -= smaller;
            ft.update(rk_rem, -1);
            int add_idx = start + k - 1;
            int rk_add = rnk[add_idx];
            long long greater = ft.query(rk_add + 1, m);
            inv += greater;
            ft.update(rk_add, 1);
            ans = min(ans, inv);
        }
        return ans;
    }
};
# @lc code=end