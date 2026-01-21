#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();
        int low = 1, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (check(mid, s, numOps, n)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
private:
    bool check(int L, const string& s, int numOps, int n) {
        vector<long long> prefix0(n + 1, 0), prefix1(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            char ch = s[i - 1];
            prefix0[i] = prefix0[i - 1] + (ch == '0');
            prefix1[i] = prefix1[i - 1] + (ch == '1');
        }
        const long long INF = 1LL << 60;
        vector<long long> dp0(n + 1, INF), dp1(n + 1, INF);
        dp0[0] = 0;
        dp1[0] = 0;
        deque<int> dq0, dq1;
        dq0.push_back(0);
        dq1.push_back(0);
        auto get_val0 = [&](int j) -> long long {
            return dp1[j] + prefix0[j] - j;
        };
        auto get_val1 = [&](int j) -> long long {
            return dp0[j] + prefix1[j] - j;
        };
        for (int i = 1; i <= n; ++i) {
            int left = max(0, i - L);
            // dp0[i]
            while (!dq0.empty() && dq0.front() < left) dq0.pop_front();
            long long minv0 = INF;
            if (!dq0.empty()) minv0 = get_val0(dq0.front());
            dp0[i] = (long long)i - prefix0[i] + minv0;
            // dp1[i]
            while (!dq1.empty() && dq1.front() < left) dq1.pop_front();
            long long minv1 = INF;
            if (!dq1.empty()) minv1 = get_val1(dq1.front());
            dp1[i] = (long long)i - prefix1[i] + minv1;
            // add i to dq0
            while (!dq0.empty() && get_val0(dq0.back()) >= get_val0(i)) dq0.pop_back();
            dq0.push_back(i);
            // add i to dq1
            while (!dq1.empty() && get_val1(dq1.back()) >= get_val1(i)) dq1.pop_back();
            dq1.push_back(i);
        }
        long long minf = min(dp0[n], dp1[n]);
        return minf <= (long long)numOps;
    }
};
# @lc code=end