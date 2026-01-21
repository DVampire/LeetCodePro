#
# @lc app=leetcode id=3721 lang=cpp
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Node {
        int mn, mx;
        Node() : mn(0), mx(0) {}
        Node(int val) : mn(val), mx(val) {}
    };

    vector<Node> tree;
    vector<int> lazy;
    int nn;

    void build(int node, int s, int e) {
        if (s == e) {
            tree[node] = Node(0);
            return;
        }
        int m = (s + e) / 2;
        build(2 * node, s, m);
        build(2 * node + 1, m + 1, e);
        tree[node].mn = min(tree[2 * node].mn, tree[2 * node + 1].mn);
        tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx);
    }

    void push(int node, int s, int e) {
        if (lazy[node] != 0) {
            tree[node].mn += lazy[node];
            tree[node].mx += lazy[node];
            if (s != e) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int node, int s, int e, int l, int r, int val) {
        push(node, s, e);
        if (s > e || s > r || e < l) return;
        if (l <= s && e <= r) {
            lazy[node] += val;
            push(node, s, e);
            return;
        }
        int m = (s + e) / 2;
        update_range(2 * node, s, m, l, r, val);
        update_range(2 * node + 1, m + 1, e, l, r, val);
        tree[node].mn = min(tree[2 * node].mn, tree[2 * node + 1].mn);
        tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx);
    }

    int find_leftmost(int node, int s, int e, int targ) {
        push(node, s, e);
        if (tree[node].mn > targ || tree[node].mx < targ) return -2;
        if (s == e) return s;
        int m = (s + e) / 2;
        push(2 * node, s, m);
        if (tree[2 * node].mn <= targ && tree[2 * node].mx >= targ) {
            int res = find_leftmost(2 * node, s, m, targ);
            if (res != -2) return res;
        }
        push(2 * node + 1, m + 1, e);
        return find_leftmost(2 * node + 1, m + 1, e, targ);
    }

    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        nn = n;
        tree.resize(4 * n + 10);
        lazy.resize(4 * n + 10, 0);
        build(1, 0, n - 1);
        vector<int> clast(100010, -1);
        int sze = 0, szo = 0;
        int ans = 0;
        for (int r = 0; r < n; ++r) {
            int v = nums[r];
            int oldp = clast[v];
            bool isev = (v % 2 == 0);
            if (oldp == -1) {
                // new
                int delta = isev ? 1 : -1;
                update_range(1, 0, n - 1, r, n - 1, delta);
                if (isev) ++sze;
                else ++szo;
            } else {
                int delta = isev ? -1 : 1;
                if (oldp <= r - 1) {
                    update_range(1, 0, n - 1, oldp, r - 1, delta);
                }
            }
            clast[v] = r;
            int targ = sze - szo;
            int clen = 0;
            if (targ == 0) {
                clen = r + 1;
            }
            int x = find_leftmost(1, 0, n - 1, targ);
            if (x != -2) {
                clen = max(clen, r - x);
            }
            ans = max(ans, clen);
        }
        return ans;
    }
};
# @lc code=end