#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3425 lang=cpp
 *
 * [3425] Longest Special Path
 */

// @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = (int)nums.size();
        vector<vector<pair<int,int>>> g(n);
        g.assign(n, {});
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        const int MAXV = 50000;
        vector<int> lastPos(MAXV + 1, -1);

        vector<long long> pathDist; // dist from root along current path, indexed by depth
        pathDist.reserve(n);

        int L = 0; // current sliding window start (depth index)
        long long bestLen = 0;
        int bestNodes = 1;

        struct Frame {
            int u, p;
            long long dist;
            int state;   // 0 enter, 1 exit
            int prevLast;
            int prevL;
            int val;
        };

        vector<Frame> st;
        st.reserve(2 * n);
        st.push_back({0, -1, 0LL, 0, 0, 0, 0});

        while (!st.empty()) {
            Frame cur = st.back();
            st.pop_back();

            if (cur.state == 0) {
                int u = cur.u;
                int val = nums[u];
                int depth = (int)pathDist.size();

                int prevLast = lastPos[val];
                int prevL = L;

                // enter
                pathDist.push_back(cur.dist);
                L = max(L, prevLast + 1);
                lastPos[val] = depth;

                long long len = cur.dist - pathDist[L];
                int nodes = depth - L + 1;

                if (len > bestLen) {
                    bestLen = len;
                    bestNodes = nodes;
                } else if (len == bestLen) {
                    bestNodes = min(bestNodes, nodes);
                }

                // exit frame
                st.push_back({u, cur.p, cur.dist, 1, prevLast, prevL, val});

                // children
                for (auto &pr : g[u]) {
                    int v = pr.first;
                    int w = pr.second;
                    if (v == cur.p) continue;
                    st.push_back({v, u, cur.dist + w, 0, 0, 0, 0});
                }
            } else {
                // exit: rollback
                lastPos[cur.val] = cur.prevLast;
                L = cur.prevL;
                pathDist.pop_back();
            }
        }

        return {(int)bestLen, bestNodes};
    }
};
// @lc code=end
