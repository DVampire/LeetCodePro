#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int _k, vector<vector<int>>& queries) {
        int n = nums.size();
        long long k = _k;
        vector<long long> mods(n), p(n);
        for (int i = 0; i < n; ++i) {
            long long num = nums[i];
            mods[i] = num % k;
            p[i] = num / k;
        }

        // Prefix sum for total sum of p
        vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + p[i - 1];
        }

        // Sparse table for min/max mods
        const int LOG = 17;
        vector<vector<long long>> spmin(LOG, vector<long long>(n));
        vector<vector<long long>> spmax(LOG, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            spmin[0][i] = spmax[0][i] = mods[i];
        }
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                spmin[j][i] = min(spmin[j - 1][i], spmin[j - 1][i + (1 << (j - 1))]);
                spmax[j][i] = max(spmax[j - 1][i], spmax[j - 1][i + (1 << (j - 1))]);
            }
        }
        auto get_min = [&](int l, int r) -> long long {
            int len = r - l + 1;
            int j = 31 - __builtin_clz(len);
            return min(spmin[j][l], spmin[j][r - (1 << j) + 1]);
        };
        auto get_max = [&](int l, int r) -> long long {
            int len = r - l + 1;
            int j = 31 - __builtin_clz(len);
            return max(spmax[j][l], spmax[j][r - (1 << j) + 1]);
        };

        // Merge-sort tree
        int tsize = 4 * n;
        vector<vector<long long>> tree_sorted(tsize);
        vector<vector<long long>> tree_prefix(tsize);

        function<void(int, int, int)> build = [&](int node, int start, int end) {
            if (start == end) {
                tree_sorted[node] = {p[start]};
                tree_prefix[node] = {0LL, p[start]};
                return;
            }
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            vector<long long>& left = tree_sorted[2 * node];
            vector<long long>& right = tree_sorted[2 * node + 1];
            vector<long long> merged;
            merged.reserve(left.size() + right.size());
            merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(merged));
            tree_sorted[node] = std::move(merged);
            int sz = tree_sorted[node].size();
            tree_prefix[node].resize(sz + 1);
            tree_prefix[node][0] = 0;
            for (int i = 1; i <= sz; ++i) {
                tree_prefix[node][i] = tree_prefix[node][i - 1] + tree_sorted[node][i - 1];
            }
        };
        build(1, 0, n - 1);

        function<pair<long long, long long>(int, int, int, int, int, long long)> query_sumcnt =
            [&](int node, int start, int end, int ql, int qr, long long val) -> pair<long long, long long> {
                if (qr < start || ql > end) return {0, 0};
                if (ql <= start && end <= qr) {
                    auto& v = tree_sorted[node];
                    auto it = upper_bound(v.begin(), v.end(), val);
                    int pos = it - v.begin();
                    long long cnt = pos;
                    long long sm = tree_prefix[node][pos];
                    return {cnt, sm};
                }
                int mid = (start + end) / 2;
                auto left = query_sumcnt(2 * node, start, mid, ql, qr, val);
                auto right = query_sumcnt(2 * node + 1, mid + 1, end, ql, qr, val);
                return {left.first + right.first, left.second + right.second};
            };

        auto get_count = [&](int l, int r, long long val) -> long long {
            return query_sumcnt(1, 0, n - 1, l, r, val).first;
        };
        auto get_sum = [&](int l, int r, long long val) -> long long {
            return query_sumcnt(1, 0, n - 1, l, r, val).second;
        };

        auto find_median = [&](int l, int r) -> long long {
            int len = r - l + 1;
            long long target_k = (len + 1LL) / 2;
            long long low = 0, high = 2000000000LL;
            while (low < high) {
                long long midv = low + (high - low) / 2;
                if (get_count(l, r, midv) >= target_k) {
                    high = midv;
                } else {
                    low = midv + 1;
                }
            }
            return low;
        };

        // Process queries
        vector<long long> ans;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            long long minm = get_min(l, r);
            long long maxm = get_max(l, r);
            if (minm != maxm) {
                ans.push_back(-1);
                continue;
            }
            long long med = find_median(l, r);
            long long total_sum = presum[r + 1] - presum[l];
            long long cnt_leq = get_count(l, r, med);
            long long sum_leq = get_sum(l, r, med);
            long long cnt_gt = (r - l + 1LL) - cnt_leq;
            long long sum_gt = total_sum - sum_leq;
            long long ops = cnt_leq * med - sum_leq + sum_gt - cnt_gt * med;
            ans.push_back(ops);
        }
        return ans;
    }
};
# @lc code=end
