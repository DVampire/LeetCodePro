#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3525 lang=cpp
 *
 * [3525] Find X Value of Array II
 */

// @lc code=start
class Solution {
public:
    int K;

    struct Node {
        int prod;
        array<int, 5> cnt;
        Node(int p = 1) : prod(p) { cnt.fill(0); }
    };

    Node identity() {
        Node n;
        n.prod = (K == 1 ? 0 : 1 % K);
        n.cnt.fill(0);
        return n;
    }

    Node makeLeaf(int val) {
        Node n;
        n.prod = val % K;
        n.cnt.fill(0);
        n.cnt[n.prod] = 1; // the only non-empty prefix is itself
        return n;
    }

    Node mergeNode(const Node &a, const Node &b) {
        Node res;
        res.cnt.fill(0);
        res.prod = (int)((1LL * a.prod * b.prod) % K);

        // prefixes entirely in a
        for (int r = 0; r < K; r++) res.cnt[r] += a.cnt[r];

        // prefixes that include all of a and then a prefix of b
        for (int rb = 0; rb < K; rb++) {
            int r = (int)((1LL * a.prod * rb) % K);
            res.cnt[r] += b.cnt[rb];
        }
        return res;
    }

    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        K = k;
        int n = (int)nums.size();

        vector<Node> seg(2 * n);
        for (int i = 0; i < n; i++) seg[n + i] = makeLeaf(nums[i]);
        for (int i = n - 1; i >= 1; i--) seg[i] = mergeNode(seg[i << 1], seg[i << 1 | 1]);

        auto update = [&](int pos, int val) {
            int p = pos + n;
            seg[p] = makeLeaf(val);
            for (p >>= 1; p >= 1; p >>= 1) {
                seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
                if (p == 1) break;
            }
        };

        auto query = [&](int l, int r) { // [l, r)
            Node left = identity();
            Node right = identity();
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) left = mergeNode(left, seg[l++]);
                if (r & 1) right = mergeNode(seg[--r], right);
            }
            return mergeNode(left, right);
        };

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            update(index, value);
            Node res = query(start, n);
            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};
// @lc code=end
