#
# @lc app=leetcode id=3525 lang=cpp
#
# [3525] Find X Value of Array II
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int prod;
    int counts[5];

    Node() {
        prod = 1;
        for (int i = 0; i < 5; ++i) counts[i] = 0;
    }
};

class Solution {
    int K;
    vector<Node> tree;
    int n;

    Node merge(const Node& A, const Node& B) {
        Node res;
        res.prod = (A.prod * B.prod) % K;
        for (int i = 0; i < K; ++i) {
            res.counts[i] = A.counts[i];
        }
        for (int i = 0; i < K; ++i) {
            if (B.counts[i] > 0) {
                res.counts[(A.prod * i) % K] += B.counts[i];
            }
        }
        return res;
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            int val = nums[start] % K;
            tree[node].prod = val;
            for (int i = 0; i < K; ++i) tree[node].counts[i] = 0;
            tree[node].counts[val] = 1;
            return;
        }
        int mid = (start + end) / 2;
        build(nums, 2 * node, start, mid);
        build(nums, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            int v = val % K;
            tree[node].prod = v;
            for (int i = 0; i < K; ++i) tree[node].counts[i] = 0;
            tree[node].counts[v] = 1;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int start, int end, int L, int R) {
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        if (R <= mid) return query(2 * node, start, mid, L, R);
        if (L > mid) return query(2 * node + 1, mid + 1, end, L, R);
        return merge(query(2 * node, start, mid, L, mid), query(2 * node + 1, mid + 1, end, mid + 1, R));
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->K = k;
        this->n = nums.size();
        tree.assign(4 * n + 1, Node());
        build(nums, 1, 0, n - 1);

        vector<int> results;
        results.reserve(queries.size());

        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, idx, val);
            Node resNode = query(1, 0, n - 1, start, n - 1);
            results.push_back(resNode.counts[x]);
        }

        return results;
    }
};
# @lc code=end