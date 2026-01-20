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

class Solution {
    struct Node {
        int count;
        long long sum;
        int left;
        int right;
    };

    vector<Node> tree;
    vector<int> roots;
    int num_nodes = 0;
    int n_distinct;

    int build(int l, int r) {
        int node = num_nodes++;
        tree.push_back({0, 0, -1, -1});
        if (l == r) return node;
        int mid = l + (r - l) / 2;
        tree[node].left = build(l, mid);
        tree[node].right = build(mid + 1, r);
        return node;
    }

    int update(int prev_node, int l, int r, int idx, long long val) {
        int node = num_nodes++;
        tree.push_back(tree[prev_node]); // Copy previous node
        tree[node].count++;
        tree[node].sum += val;
        
        if (l == r) return node;
        
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            tree[node].left = update(tree[prev_node].left, l, mid, idx, val);
        } else {
            tree[node].right = update(tree[prev_node].right, mid + 1, r, idx, val);
        }
        return node;
    }

    // Returns sum of smallest k elements in the range defined by roots[R] and roots[L-1]
    long long querySum(int node_l, int node_r, int l, int r, int k) {
        if (k <= 0) return 0;
        if (l == r) {
            // All elements in this leaf are the same value.
            // We need k of them.
            // Calculate value from sum/count of the diff (or just store value in leaf, but sum/count works)
            long long val = (tree[node_r].sum - tree[node_l].sum) / (tree[node_r].count - tree[node_l].count);
            return val * k;
        }

        int mid = l + (r - l) / 2;
        int left_count = tree[tree[node_r].left].count - tree[tree[node_l].left].count;
        
        if (k <= left_count) {
            return querySum(tree[node_l].left, tree[node_r].left, l, mid, k);
        } else {
            long long left_sum = tree[tree[node_r].left].sum - tree[tree[node_l].left].sum;
            return left_sum + querySum(tree[node_l].right, tree[node_r].right, mid + 1, r, k - left_count);
        }
    }

public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        
        // 1. Precompute modulo validity
        vector<int> bad_indices;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] % k != nums[i+1] % k) {
                bad_indices.push_back(i);
            }
        }

        // 2. Prepare values for PST
        vector<long long> vals(n);
        vector<long long> distinct_vals;
        for (int i = 0; i < n; ++i) {
            vals[i] = (long long)nums[i] / k;
            distinct_vals.push_back(vals[i]);
        }
        
        sort(distinct_vals.begin(), distinct_vals.end());
        distinct_vals.erase(unique(distinct_vals.begin(), distinct_vals.end()), distinct_vals.end());
        n_distinct = distinct_vals.size();

        auto get_rank = [&](long long val) {
            return lower_bound(distinct_vals.begin(), distinct_vals.end(), val) - distinct_vals.begin();
        };

        // 3. Build PST
        // Reserve memory to prevent reallocation invalidating pointers/indices if we used pointers,
        // but we use indices so it's safer, though resizing is still costly. Estimate size.
        // N updates, each adds ~logN nodes. 40000 * 16 approx 640000.
        tree.reserve(n * 20);
        roots.resize(n + 1);
        roots[0] = build(0, n_distinct - 1);

        for (int i = 0; i < n; ++i) {
            int rank = get_rank(vals[i]);
            roots[i + 1] = update(roots[i], 0, n_distinct - 1, rank, vals[i]);
        }

        // 4. Prefix sums for O(1) total range sum
        vector<long long> prefix_sum_vals(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum_vals[i + 1] = prefix_sum_vals[i] + vals[i];
        }

        vector<long long> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // Check modulo validity
            // We need to check if there is any bad index in [l, r-1]
            auto it = lower_bound(bad_indices.begin(), bad_indices.end(), l);
            if (it != bad_indices.end() && *it < r) {
                ans.push_back(-1);
                continue;
            }

            int len = r - l + 1;
            int mid_idx = len / 2; // Number of elements strictly smaller than median in sorted order to consider
            
            // We need sum of smallest `mid_idx` elements
            long long sum_small = querySum(roots[l], roots[r + 1], 0, n_distinct - 1, mid_idx);
            
            // We need the median value, which is the (mid_idx + 1)-th element
            long long sum_small_plus_1 = querySum(roots[l], roots[r + 1], 0, n_distinct - 1, mid_idx + 1);
            long long median = sum_small_plus_1 - sum_small;

            long long total_sum = prefix_sum_vals[r + 1] - prefix_sum_vals[l];
            long long sum_rest = total_sum - sum_small - median;

            long long cost = (median * mid_idx - sum_small) + (sum_rest - median * (len - mid_idx - 1));
            ans.push_back(cost);
        }

        return ans;
    }
};
# @lc code=end