#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3486 lang=cpp
//
// [3486] Longest Special Path II
//

// @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = (int)nums.size();
        vector<vector<pair<int,int>>> g(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        int maxVal = 0;
        for (int x : nums) maxVal = max(maxVal, x);
        vector<vector<int>> occ(maxVal + 1);

        multiset<int> ms2; // second-from-last depth for values with >=2 occurrences
        multiset<int> ms3; // third-from-last depth for values with >=3 occurrences

        vector<int> nodeStack;
        vector<long long> distStack;
        nodeStack.reserve(n);
        distStack.reserve(n);

        long long bestLen = 0;
        int bestNodes = 1;

        auto addValueAtDepth = [&](int val, int depth) {
            auto &vec = occ[val];
            int k = (int)vec.size();

            // Remove old contributions
            if (k >= 2) {
                auto it = ms2.find(vec[k - 2]);
                if (it != ms2.end()) ms2.erase(it);
            }
            if (k >= 3) {
                auto it = ms3.find(vec[k - 3]);
                if (it != ms3.end()) ms3.erase(it);
            }

            // Insert new contributions after push (based on previous elements)
            if (k >= 1) {
                ms2.insert(vec[k - 1]);
            }
            if (k >= 2) {
                ms3.insert(vec[k - 2]);
            }

            vec.push_back(depth);
        };

        auto removeValueAtDepth = [&](int val) {
            auto &vec = occ[val];
            int k = (int)vec.size();
            // k >= 1

            // Remove current contributions (before pop)
            if (k >= 2) {
                auto it = ms2.find(vec[k - 2]);
                if (it != ms2.end()) ms2.erase(it);
            }
            if (k >= 3) {
                auto it = ms3.find(vec[k - 3]);
                if (it != ms3.end()) ms3.erase(it);
            }

            // Insert new contributions after pop
            if (k >= 3) {
                ms2.insert(vec[k - 3]);
            }
            if (k >= 4) {
                ms3.insert(vec[k - 4]);
            }

            vec.pop_back();
        };

        auto currentLeftBoundary = [&]() -> int {
            int l = 0;
            if (!ms3.empty()) {
                l = max(l, *ms3.rbegin() + 1);
            }
            if ((int)ms2.size() >= 2) {
                auto rit = ms2.rbegin();
                ++rit; // second largest
                l = max(l, *rit + 1);
            }
            return l;
        };

        struct Frame {
            int u, p;
            int it;
            long long dist;
        };

        vector<Frame> st;
        st.reserve(n);

        // enter root
        st.push_back({0, -1, 0, 0LL});
        {
            int depth = 0;
            nodeStack.push_back(0);
            distStack.push_back(0LL);
            addValueAtDepth(nums[0], depth);

            int l = currentLeftBoundary();
            long long len = distStack[depth] - distStack[l];
            int nodes = depth - l + 1;
            if (len > bestLen) {
                bestLen = len;
                bestNodes = nodes;
            } else if (len == bestLen) {
                bestNodes = min(bestNodes, nodes);
            }
        }

        while (!st.empty()) {
            Frame &fr = st.back();
            int u = fr.u;
            if (fr.it == (int)g[u].size()) {
                // exit node
                int depth = (int)nodeStack.size() - 1;
                removeValueAtDepth(nums[u]);
                nodeStack.pop_back();
                distStack.pop_back();
                st.pop_back();
                continue;
            }

            auto [v, w] = g[u][fr.it++];
            if (v == fr.p) continue;

            long long ndist = fr.dist + w;
            st.push_back({v, u, 0, ndist});

            int depth = (int)nodeStack.size();
            nodeStack.push_back(v);
            distStack.push_back(ndist);
            addValueAtDepth(nums[v], depth);

            int l = currentLeftBoundary();
            long long len = distStack[depth] - distStack[l];
            int nodes = depth - l + 1;
            if (len > bestLen) {
                bestLen = len;
                bestNodes = nodes;
            } else if (len == bestLen) {
                bestNodes = min(bestNodes, nodes);
            }
        }

        return { (int)bestLen, bestNodes };
    }
};
// @lc code=end
