#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
    int count;
    long long sum;
    int left, right;
};

class Solution {
    vector<Node> tree;
    vector<int> roots;
    int node_count;

    int update(int prev_root, int l, int r, int val, int original_val) {
        int node = ++node_count;
        tree[node] = tree[prev_root];
        tree[node].count++;
        tree[node].sum += original_val;
        if (l == r) return node;
        int mid = l + (r - l) / 2;
        if (val <= mid) tree[node].left = update(tree[prev_root].left, l, mid, val, original_val);
        else tree[node].right = update(tree[prev_root].right, mid + 1, r, val, original_val);
        return node;
    }

    pair<int, long long> query(int node_l, int node_r, int l, int r, int k) {
        if (l == r) return {tree[node_r].count - tree[node_l].count, tree[node_r].sum - tree[node_l].sum};
        int mid = l + (r - l) / 2;
        int left_count = tree[tree[node_r].left].count - tree[tree[node_l].left].count;
        if (k <= left_count) return query(tree[node_l].left, tree[node_r].left, l, mid, k);
        else {
            pair<int, long long> res = query(tree[node_l].right, tree[node_r].right, mid + 1, r, k - left_count);
            res.first += left_count;
            res.second += tree[tree[node_r].left].sum - tree[tree[node_l].left].sum;
            return res;
        }
    }

    long long get_sum_less(int node_l, int node_r, int l, int r, int k) {
        if (k <= 0) return 0;
        if (k >= tree[node_r].count - tree[node_l].count) return tree[node_r].sum - tree[node_l].sum;
        int mid = l + (r - l) / 2;
        int left_count = tree[tree[node_r].left].count - tree[tree[node_l].left].count;
        if (k <= left_count) return get_sum_less(tree[node_l].left, tree[node_r].left, l, mid, k);
        else return (tree[tree[node_r].left].sum - tree[tree[node_l].left].sum) + get_sum_less(tree[node_l].right, tree[node_r].right, mid + 1, r, k - left_count);
    }

public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> rems(n);
        vector<int> mods_check(n + 1, 0);
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        int m = vals.size();
        tree.assign(n * 40, {0, 0, 0, 0});
        roots.assign(n + 1, 0);
        node_count = 0;

        for (int i = 0; i < n; ++i) {
            rems[i] = nums[i] % k;
            mods_check[i+1] = mods_check[i] + (i > 0 && rems[i] != rems[i-1]);
            int idx = lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin();
            roots[i+1] = update(roots[i], 0, m - 1, idx, nums[i]);
        }

        vector<long long> ans;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            if (mods_check[r+1] - mods_check[l+1] > 0) {
                ans.push_back(-1);
                continue;
            }
            int len = r - l + 1;
            int mid_idx = (len + 1) / 2;
            pair<int, long long> median_info = query(roots[l], roots[r+1], 0, m - 1, mid_idx);
            long long median = vals[lower_bound(vals.begin(), vals.end(), (int)(median_info.second / median_info.first)) - vals.begin()];
            // Since query returns the k-th element info, we need the actual value
            // Let's refine the median finding.
            int low = 0, high = m - 1, target_idx = mid_idx;
            int cur_l = roots[l], cur_r = roots[r+1];
            while(low < high) {
                int mid_val = low + (high - low) / 2;
                int left_count = tree[tree[cur_r].left].count - tree[tree[cur_l].left].count;
                if (target_idx <= left_count) {
                    cur_l = tree[cur_l].left; cur_r = tree[cur_r].left;
                    high = mid_val;
                } else {
                    target_idx -= left_count;
                    cur_l = tree[cur_l].right; cur_r = tree[cur_r].right;
                    low = mid_val + 1;
                }
            }
            long long med_val = vals[low];
            long long sum_less = get_sum_less(roots[l], roots[r+1], 0, m - 1, mid_idx);
            long long total_sum = tree[roots[r+1]].sum - tree[roots[l]].sum;
            long long ops = (med_val * mid_idx - sum_less) + ((total_sum - sum_less) - med_val * (len - mid_idx));
            ans.push_back(ops / k);
        }
        return ans;
    }
};
# @lc code=end