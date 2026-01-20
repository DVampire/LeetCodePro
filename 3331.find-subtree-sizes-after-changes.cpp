#include <bits/stdc++.h>
using namespace std;

#
# @lc app=leetcode id=3331 lang=cpp
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = (int)parent.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) children[parent[i]].push_back(i);

        // Step 1: compute newParent using DFS on original tree
        vector<int> newParent = parent;
        newParent[0] = -1;

        array<vector<int>, 26> pathStacks; // nodes on current path per character

        // iterative DFS with enter/exit states
        vector<pair<int,int>> st;
        st.reserve(2 * n);
        st.push_back({0, 0}); // (node, state) state: 0=enter, 1=exit

        while (!st.empty()) {
            auto [u, state] = st.back();
            st.pop_back();
            int c = s[u] - 'a';

            if (state == 0) {
                // enter
                if (u != 0) {
                    if (!pathStacks[c].empty()) newParent[u] = pathStacks[c].back();
                    else newParent[u] = parent[u];
                }
                pathStacks[c].push_back(u);

                st.push_back({u, 1});
                // push children in reverse to keep natural order (not required)
                for (int i = (int)children[u].size() - 1; i >= 0; --i) {
                    st.push_back({children[u][i], 0});
                }
            } else {
                // exit
                pathStacks[c].pop_back();
            }
        }

        // Step 2: build final tree adjacency
        vector<vector<int>> finalChildren(n);
        for (int i = 1; i < n; i++) {
            finalChildren[newParent[i]].push_back(i);
        }

        // Step 3: compute subtree sizes in final tree using reverse DFS order
        vector<int> order;
        order.reserve(n);
        vector<int> stack2;
        stack2.reserve(n);
        stack2.push_back(0);
        while (!stack2.empty()) {
            int u = stack2.back();
            stack2.pop_back();
            order.push_back(u);
            for (int v : finalChildren[u]) stack2.push_back(v);
        }

        vector<int> sz(n, 1);
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            long long sum = 1;
            for (int v : finalChildren[u]) sum += sz[v];
            sz[u] = (int)sum;
        }

        return sz;
    }
};
# @lc code=end
