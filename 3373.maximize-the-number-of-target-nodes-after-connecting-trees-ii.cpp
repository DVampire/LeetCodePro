#
# @lc app=leetcode id=3373 lang=cpp
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#
#include <bits/stdc++.h>
using namespace std;

# @lc code=start
class Solution {
    pair<vector<int>, array<int,2>> colorTree(int N, const vector<vector<int>>& edges) {
        vector<vector<int>> g(N);
        g.reserve(N);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> color(N, -1);
        array<int,2> cnt{0,0};

        // Tree is connected; start from 0.
        deque<int> dq;
        color[0] = 0;
        cnt[0] = 1;
        dq.push_back(0);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    cnt[color[v]]++;
                    dq.push_back(v);
                }
            }
        }
        return {color, cnt};
    }

public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = (int)edges1.size() + 1;
        int m = (int)edges2.size() + 1;

        auto [c1, cnt1] = colorTree(n, edges1);
        auto [c2, cnt2] = colorTree(m, edges2);

        int best2 = max(cnt2[0], cnt2[1]);
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = cnt1[c1[i]] + best2;
        }
        return ans;
    }
};
# @lc code=end
