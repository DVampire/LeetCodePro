#
# @lc app=leetcode id=3425 lang=cpp
#
# [3425] Longest Special Path
#

# @lc code=start
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

        int maxVal = 50001; // nums[i] <= 5e4
        vector<int> last(maxVal, -1);

        struct Frame {
            int u, p;
            int idx;
            int L_before;
            int L_after;
            int prevLast;
            long long dist;
        };

        long long bestLen = 0;
        int bestNodes = 1;

        vector<long long> pathDist; // distance from root to node at each stack position
        pathDist.reserve(n);

        vector<Frame> st;
        st.reserve(n);

        auto enterNode = [&](int u, int p, long long dist, int L_before) {
            int pos = (int)pathDist.size();
            int v = nums[u];
            int prevLast = last[v];
            int L_after = L_before;
            if (prevLast != -1) L_after = max(L_after, prevLast + 1);

            last[v] = pos;
            pathDist.push_back(dist);

            long long len = dist - pathDist[L_after];
            int nodesCnt = pos - L_after + 1;
            if (len > bestLen) {
                bestLen = len;
                bestNodes = nodesCnt;
            } else if (len == bestLen) {
                bestNodes = min(bestNodes, nodesCnt);
            }

            st.push_back(Frame{u, p, 0, L_before, L_after, prevLast, dist});
        };

        enterNode(0, -1, 0LL, 0);

        while (!st.empty()) {
            Frame &f = st.back();
            int u = f.u;

            if (f.idx < (int)g[u].size()) {
                auto [v, w] = g[u][f.idx++];
                if (v == f.p) continue;
                enterNode(v, u, f.dist + (long long)w, f.L_after);
            } else {
                // exit node: restore state
                int val = nums[u];
                last[val] = f.prevLast;
                pathDist.pop_back();
                st.pop_back();
            }
        }

        return { (int)bestLen, bestNodes };
    }
};
# @lc code=end
