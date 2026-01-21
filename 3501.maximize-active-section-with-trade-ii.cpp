#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3501 lang=cpp
//
// [3501] Maximize Active Section with Trade II
//

// @lc code=start
class Solution {
    struct Node {
        int len = 0;
        int ones = 0;

        int pref0 = 0, suff0 = 0, max0 = 0;

        // first two runs (from left)
        int firstType = -1, firstLen = 0;
        int secondType = -1, secondLen = 0;
        // last two runs (from right)
        int lastType = -1, lastLen = 0;
        int secondLastType = -1, secondLastLen = 0;

        int minInternalOneLen = INT_MAX; // eligible 1-run surrounded by 0s
        int maxAdjZeroSum = 0;           // max(leftZero + rightZero) around such a 1-run
    };

    static void appendRun(vector<pair<int,int>> &runs, int type, int len) {
        if (type == -1 || len == 0) return;
        if (!runs.empty() && runs.back().first == type) runs.back().second += len;
        else runs.push_back({type, len});
    }

    static Node mergeNode(const Node &a, const Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node c;
        c.len = a.len + b.len;
        c.ones = a.ones + b.ones;

        // prefix/suffix zeros
        c.pref0 = (a.pref0 == a.len) ? a.len + b.pref0 : a.pref0;
        c.suff0 = (b.suff0 == b.len) ? b.len + a.suff0 : b.suff0;

        c.max0 = max(a.max0, b.max0);
        if (a.suff0 > 0 && b.pref0 > 0) c.max0 = max(c.max0, a.suff0 + b.pref0);

        // Build first two runs of combined segment
        vector<pair<int,int>> pre;
        appendRun(pre, a.firstType, a.firstLen);
        appendRun(pre, a.secondType, a.secondLen);
        appendRun(pre, b.firstType, b.firstLen);
        appendRun(pre, b.secondType, b.secondLen);
        if ((int)pre.size() > 2) pre.resize(2);
        c.firstType = pre[0].first;
        c.firstLen = pre[0].second;
        if ((int)pre.size() == 2) {
            c.secondType = pre[1].first;
            c.secondLen = pre[1].second;
        }

        // Build last two runs of combined segment (from right, using reverse accumulation)
        vector<pair<int,int>> rev;
        appendRun(rev, b.lastType, b.lastLen);
        appendRun(rev, b.secondLastType, b.secondLastLen);
        appendRun(rev, a.lastType, a.lastLen);
        appendRun(rev, a.secondLastType, a.secondLastLen);
        if ((int)rev.size() > 2) rev.resize(2);
        c.lastType = rev[0].first;
        c.lastLen = rev[0].second;
        if ((int)rev.size() == 2) {
            c.secondLastType = rev[1].first;
            c.secondLastLen = rev[1].second;
        }

        // Internal metrics from children
        c.minInternalOneLen = min(a.minInternalOneLen, b.minInternalOneLen);
        c.maxAdjZeroSum = max(a.maxAdjZeroSum, b.maxAdjZeroSum);

        // Candidates created/affected at the boundary
        // Case 1: boundary is 1|1, spanning ones run
        if (a.lastType == 1 && b.firstType == 1) {
            int leftZero = (a.secondLastType == 0 ? a.secondLastLen : 0);
            int rightZero = (b.secondType == 0 ? b.secondLen : 0);
            if (leftZero > 0 && rightZero > 0) {
                c.minInternalOneLen = min(c.minInternalOneLen, a.lastLen + b.firstLen);
                c.maxAdjZeroSum = max(c.maxAdjZeroSum, leftZero + rightZero);
            }
        }
        // Case 2: boundary is 1|0, left suffix ones run may become internal
        if (a.lastType == 1 && b.firstType == 0) {
            int leftZero = (a.secondLastType == 0 ? a.secondLastLen : 0);
            int rightZero = b.firstLen;
            if (leftZero > 0 && rightZero > 0) {
                c.minInternalOneLen = min(c.minInternalOneLen, a.lastLen);
                c.maxAdjZeroSum = max(c.maxAdjZeroSum, leftZero + rightZero);
            }
        }
        // Case 3: boundary is 0|1, right prefix ones run may become internal
        if (a.lastType == 0 && b.firstType == 1) {
            int leftZero = a.lastLen;
            int rightZero = (b.secondType == 0 ? b.secondLen : 0);
            if (leftZero > 0 && rightZero > 0) {
                c.minInternalOneLen = min(c.minInternalOneLen, b.firstLen);
                c.maxAdjZeroSum = max(c.maxAdjZeroSum, leftZero + rightZero);
            }
        }

        return c;
    }

    static Node makeLeaf(char ch) {
        Node x;
        x.len = 1;
        int t = ch - '0';
        x.firstType = x.lastType = t;
        x.firstLen = x.lastLen = 1;
        x.secondType = x.secondLastType = -1;
        x.secondLen = x.secondLastLen = 0;

        x.ones = (t == 1);
        x.pref0 = x.suff0 = x.max0 = (t == 0 ? 1 : 0);

        x.minInternalOneLen = INT_MAX;
        x.maxAdjZeroSum = 0;
        return x;
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = (int)s.size();
        int size = 1;
        while (size < n) size <<= 1;
        vector<Node> seg(2 * size);

        for (int i = 0; i < n; i++) seg[size + i] = makeLeaf(s[i]);
        for (int i = size - 1; i >= 1; i--) seg[i] = mergeNode(seg[i << 1], seg[i << 1 | 1]);

        auto rangeQuery = [&](int l, int r) {
            Node leftAcc, rightAcc;
            l += size; r += size;
            while (l <= r) {
                if (l & 1) leftAcc = mergeNode(leftAcc, seg[l++]);
                if (!(r & 1)) rightAcc = mergeNode(seg[r--], rightAcc);
                l >>= 1; r >>= 1;
            }
            return mergeNode(leftAcc, rightAcc);
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            int l = q[0], r = q[1];
            Node node = rangeQuery(l, r);
            int baseOnes = node.ones;
            if (node.minInternalOneLen == INT_MAX) {
                ans.push_back(baseOnes);
                continue;
            }
            int bestGain = max(node.maxAdjZeroSum, node.max0 - node.minInternalOneLen);
            if (bestGain < 0) bestGain = 0;
            ans.push_back(baseOnes + bestGain);
        }
        return ans;
    }
};
// @lc code=end
