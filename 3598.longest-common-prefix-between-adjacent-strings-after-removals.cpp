#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3598 lang=cpp
 *
 * [3598] Longest Common Prefix Between Adjacent Strings After Removals
 */

// @lc code=start
class Solution {
    static int lcpLen(const string& a, const string& b) {
        int m = (int)min(a.size(), b.size());
        int i = 0;
        while (i < m && a[i] == b[i]) ++i;
        return i;
    }

public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = (int)words.size();
        if (n == 1) return vector<int>(1, 0);

        vector<int> adj(max(0, n - 1), 0);
        for (int i = 0; i + 1 < n; ++i) {
            adj[i] = lcpLen(words[i], words[i + 1]);
        }

        int m = (int)adj.size();
        vector<int> pref(m, 0), suf(m, 0);
        if (m > 0) {
            pref[0] = adj[0];
            for (int i = 1; i < m; ++i) pref[i] = max(pref[i - 1], adj[i]);
            suf[m - 1] = adj[m - 1];
            for (int i = m - 2; i >= 0; --i) suf[i] = max(suf[i + 1], adj[i]);
        }

        vector<int> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            int leftMax = (i >= 2) ? pref[i - 2] : 0;
            int rightMax = (i + 1 <= n - 2) ? suf[i + 1] : 0;
            int base = max(leftMax, rightMax);

            int bridge = 0;
            if (i > 0 && i < n - 1) {
                bridge = lcpLen(words[i - 1], words[i + 1]);
            }

            ans[i] = max(base, bridge);
        }
        return ans;
    }
};
// @lc code=end
