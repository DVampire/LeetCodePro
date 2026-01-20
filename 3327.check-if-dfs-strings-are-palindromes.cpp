#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3327 lang=cpp
//
// [3327] Check if DFS Strings Are Palindromes
//

// @lc code=start
class Solution {
    struct RH {
        long long mod, base;
        vector<long long> pwr, pref;

        RH(long long mod_, long long base_, const string &t) : mod(mod_), base(base_) {
            int n = (int)t.size();
            pwr.assign(n + 1, 1);
            pref.assign(n + 1, 0);
            for (int i = 0; i < n; i++) {
                pwr[i + 1] = (long long)((__int128)pwr[i] * base % mod);
                long long v = (t[i] - 'a' + 1);
                pref[i + 1] = (long long)((((__int128)pref[i] * base) + v) % mod);
            }
        }

        long long get(int l, int r) const { // inclusive
            long long res = (pref[r + 1] - (long long)((__int128)pref[l] * pwr[r - l + 1] % mod)) % mod;
            if (res < 0) res += mod;
            return res;
        }
    };

public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = (int)parent.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) children[parent[i]].push_back(i);
        for (int i = 0; i < n; i++) sort(children[i].begin(), children[i].end());

        // Iterative postorder DFS from root=0.
        vector<int> sub(n, 0), tout(n, -1);
        vector<int> order; order.reserve(n);

        struct Frame { int x; int idx; };
        vector<Frame> st;
        st.reserve(n);
        st.push_back({0, 0});
        sub[0] = 1;

        while (!st.empty()) {
            auto &f = st.back();
            int x = f.x;
            if (f.idx < (int)children[x].size()) {
                int y = children[x][f.idx++];
                st.push_back({y, 0});
                sub[y] = 1;
            } else {
                st.pop_back();
                tout[x] = (int)order.size();
                order.push_back(x);
                if (!st.empty()) {
                    sub[st.back().x] += sub[x];
                }
            }
        }

        // Build postorder string T
        string T; T.resize(n);
        for (int i = 0; i < n; i++) T[i] = s[order[i]];
        string R = T;
        reverse(R.begin(), R.end());

        const long long MOD1 = 1000000007LL;
        const long long MOD2 = 1000000009LL;
        const long long BASE = 911382323LL;

        RH h1(MOD1, BASE, T), h2(MOD2, BASE, T);
        RH rh1(MOD1, BASE, R), rh2(MOD2, BASE, R);

        vector<bool> ans(n, false);
        for (int i = 0; i < n; i++) {
            int r = tout[i];
            int len = sub[i];
            int l = r - len + 1;

            int rl = n - 1 - r;
            int rr = n - 1 - l;

            bool ok = (h1.get(l, r) == rh1.get(rl, rr)) && (h2.get(l, r) == rh2.get(rl, rr));
            ans[i] = ok;
        }
        return ans;
    }
};
// @lc code=end
