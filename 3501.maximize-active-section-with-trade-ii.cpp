#
# @lc app=leetcode id=3501 lang=cpp
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

struct Island {
    int start, endd, a, full_bridge, ps, pe, qs, qe;
};

class SparseMax {
public:
    vector<vector<int>> st;
    vector<int> logg;
    int n;
    SparseMax(vector<int>& arr) {
        n = arr.size();
        int lg = 32 - __builtin_clz(n);
        st.assign(lg, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) st[0][i] = arr[i];
        for (int j = 1; j < lg; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
        logg.resize(n + 1);
        logg[1] = 0;
        for (int i = 2; i <= n; ++i) logg[i] = logg[i / 2] + 1;
    }
    int query(int l, int r) {
        if (l > r) return INT_MIN / 2;
        int len = r - l + 1;
        int k = logg[len];
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int total_ones = 0;
        for (char c : s) if (c == '1') ++total_ones;

        // Parse all runs
        vector<tuple<int, int, int>> all_runs; // start, len, typ
        int i = 0;
        while (i < n) {
            int st = i;
            int typ = s[i] - '0';
            while (i < n && (s[i] - '0') == typ) ++i;
            int len = i - st;
            all_runs.emplace_back(st, len, typ);
        }
        int num_runs = all_runs.size();

        // Extract islands (1-runs with prev and next 0-run)
        vector<Island> islands;
        for (int r = 1; r + 1 < num_runs; ++r) {
            auto [st1, len1, typ1] = all_runs[r];
            if (typ1 != 1) continue;
            auto [st0p, lenp, typp] = all_runs[r - 1];
            auto [st0n, lenn, typn] = all_runs[r + 1];
            if (typp != 0 || typn != 0) continue;
            int istart = st1;
            int iend = st1 + len1 - 1;
            int ia = len1;
            int ps = st0p;
            int pe = ps + lenp - 1;
            int qs = iend + 1;
            int qe = qs + lenn - 1;
            int fbridge = lenp + lenn;
            islands.push_back({istart, iend, ia, fbridge, ps, pe, qs, qe});
        }
        int K = islands.size();
        if (K == 0) {
            vector<int> ans(queries.size(), total_ones);
            return ans;
        }

        // Prepare arrays
        vector<int> starts(K), ends(K), pss(K), qes(K);
        vector<int> fullb(K), vleft(K), vright(K), vboth(K);
        for (int idx = 0; idx < K; ++idx) {
            starts[idx] = islands[idx].start;
            ends[idx] = islands[idx].endd;
            pss[idx] = islands[idx].ps;
            qes[idx] = islands[idx].qe;
            fullb[idx] = islands[idx].full_bridge;
            vleft[idx] = islands[idx].full_bridge + islands[idx].ps;
            vright[idx] = islands[idx].full_bridge - islands[idx].qe;
            vboth[idx] = islands[idx].full_bridge + islands[idx].ps - islands[idx].qe;
        }

        // Sparse tables
        SparseMax sp_full(fullb);
        SparseMax sp_left(vleft);
        SparseMax sp_right(vright);
        SparseMax sp_both(vboth);

        // Process queries
        vector<int> answer;
        for (auto& q : queries) {
            int L = q[0], R = q[1];
            int ql = L + 1;
            int qr = R - 1;
            if (ql > qr) {
                answer.push_back(total_ones);
                continue;
            }

            // jj: first >= ql on starts
            auto itj = lower_bound(starts.begin(), starts.end(), ql);
            int jj = itj - starts.begin();

            // kk: last <= qr on ends
            auto itk = upper_bound(ends.begin(), ends.end(), qr);
            int kk = (itk - ends.begin()) - 1;

            if (jj > kk) {
                answer.push_back(total_ones);
                continue;
            }

            // mleft: first ps >= L
            auto itml = lower_bound(pss.begin(), pss.end(), L);
            int mleft = itml - pss.begin();

            // mright: last qe <= R
            auto itmr = upper_bound(qes.begin(), qes.end(), R);
            int mright = (itmr - qes.begin()) - 1;

            long long maxb = LLONG_MIN / 2;

            // middle
            int ms = max(jj, mleft);
            int me = min(kk, mright);
            if (ms <= me) {
                maxb = max(maxb, (long long)sp_full.query(ms, me));
            }

            // left
            int ls = jj;
            int le = min({kk, mleft - 1, mright});
            if (ls <= le) {
                int mv = sp_left.query(ls, le);
                maxb = max(maxb, (long long)mv - L);
            }

            // right
            int rs = max({jj, mright + 1, mleft});
            int re = kk;
            if (rs <= re) {
                int mv = sp_right.query(rs, re);
                maxb = max(maxb, (long long)mv + R);
            }

            // both penalties
            if (mleft > mright + 1) {
                int bs = max(jj, mright + 1);
                int be = min(kk, mleft - 1);
                if (bs <= be) {
                    int mv = sp_both.query(bs, be);
                    maxb = max(maxb, (long long)mv + R - L);
                }
            }

            int max_net = max(0LL, maxb);
            answer.push_back(total_ones + max_net);
        }
        return answer;
    }
};

# @lc code=end