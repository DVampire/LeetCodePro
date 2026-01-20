#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3310 lang=cpp
 *
 * [3310] Remove Methods From Project
 */

// @lc code=start
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> g(n);
        g.reserve(n);
        for (auto &e : invocations) {
            g[e[0]].push_back(e[1]);
        }

        // Step 1: find all suspicious methods reachable from k
        vector<char> susp(n, 0);
        vector<int> st;
        st.push_back(k);
        susp[k] = 1;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : g[u]) {
                if (!susp[v]) {
                    susp[v] = 1;
                    st.push_back(v);
                }
            }
        }

        // Step 2: check if any outside method invokes a suspicious method
        for (auto &e : invocations) {
            int a = e[0], b = e[1];
            if (!susp[a] && susp[b]) {
                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all; // cannot remove any suspicious methods
            }
        }

        // Step 3: remove all suspicious methods
        vector<int> res;
        res.reserve(n);
        for (int i = 0; i < n; i++) {
            if (!susp[i]) res.push_back(i);
        }
        return res;
    }
};
// @lc code=end
