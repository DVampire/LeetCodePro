#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        vector<int> par(n), rnk(n, 0);
        for (int i = 0; i < n; ++i) par[i] = i;
        auto find = [&](auto&& self, int x) -> int {
            return par[x] != x ? par[x] = self(self, par[x]) : x;
        };
        auto union_sets = [&](int a, int b) {
            a = find(find, a);
            b = find(find, b);
            if (a == b) return;
            if (rnk[a] < rnk[b]) swap(a, b);
            par[b] = a;
            if (rnk[a] == rnk[b]) ++rnk[a];
        };
        for (auto& sw : swaps) {
            union_sets(sw[0], sw[1]);
        }
        vector<vector<int>> comp(n);
        for (int i = 0; i < n; ++i) {
            int r = find(find, i);
            comp[r].push_back(i);
        }
        long long ans = 0;
        for (int r = 0; r < n; ++r) {
            if (comp[r].empty()) continue;
            vector<long long> vals;
            int A = 0, B = 0;
            for (int idx : comp[r]) {
                vals.push_back(nums[idx]);
                if ((idx & 1) == 0) ++A;
                else ++B;
            }
            sort(vals.rbegin(), vals.rend());
            int sz = vals.size();
            for (int j = 0; j < A; ++j) ans += vals[j];
            for (int j = A; j < sz; ++j) ans -= vals[j];
        }
        return ans;
    }
};
# @lc code=end