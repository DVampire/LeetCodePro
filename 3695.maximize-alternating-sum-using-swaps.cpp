#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
    struct DSU {
        vector<int> p, sz;
        DSU(int n = 0) { init(n); }
        void init(int n) {
            p.resize(n);
            sz.assign(n, 1);
            iota(p.begin(), p.end(), 0);
        }
        int find(int x) {
            while (p[x] != x) {
                p[x] = p[p[x]];
                x = p[x];
            }
            return x;
        }
        void unite(int a, int b) {
            a = find(a); b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            p[b] = a;
            sz[a] += sz[b];
        }
    };

public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = (int)nums.size();
        DSU dsu(n);
        for (auto &e : swaps) dsu.unite(e[0], e[1]);

        vector<vector<int>> compVals(n);
        vector<int> evenCnt(n, 0), compSize(n, 0);

        for (int i = 0; i < n; i++) {
            int r = dsu.find(i);
            compVals[r].push_back(nums[i]);
            compSize[r]++;
            if ((i & 1) == 0) evenCnt[r]++;
        }

        long long ans = 0;
        for (int r = 0; r < n; r++) {
            if (compSize[r] == 0) continue;
            auto &v = compVals[r];
            sort(v.begin(), v.end());

            int a = evenCnt[r];
            int b = compSize[r] - a;

            long long plusSum = 0, minusSum = 0;
            // smallest b go to minus positions
            for (int i = 0; i < b; i++) minusSum += v[i];
            // largest a go to plus positions
            for (int i = compSize[r] - a; i < compSize[r]; i++) plusSum += v[i];

            ans += plusSum - minusSum;
        }

        return ans;
    }
};
// @lc code=end
