#
# @lc app=leetcode id=3569 lang=cpp
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
#include <vector>
#include <set>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        const int MAXV = 100010;
        vector<int> is_prime(MAXV, 1);
        is_prime[0] = is_prime[1] = 0;
        for (long long i = 2; i * i < MAXV; ++i) {
            if (is_prime[i]) {
                for (long long j = i * i; j < MAXV; j += i) {
                    is_prime[j] = 0;
                }
            }
        }

        struct SegTree {
            int n;
            vector<int> tree, lazy;
            SegTree(int _n) : n(_n), tree(4 * _n + 10, 0), lazy(4 * _n + 10, 0) {}

            void propagate(int node, int start, int end) {
                if (lazy[node] != 0) {
                    tree[node] += lazy[node];
                    if (start != end) {
                        lazy[2 * node] += lazy[node];
                        lazy[2 * node + 1] += lazy[node];
                    }
                    lazy[node] = 0;
                }
            }

            void update_range(int node, int start, int end, int l, int r, int val) {
                propagate(node, start, end);
                if (start > end || start > r || end < l) return;
                if (start >= l && end <= r) {
                    lazy[node] += val;
                    propagate(node, start, end);
                    return;
                }
                int mid = (start + end) / 2;
                update_range(2 * node, start, mid, l, r, val);
                update_range(2 * node + 1, mid + 1, end, l, r, val);
                tree[node] = max(tree[2 * node], tree[2 * node + 1]);
            }

            void update(int l, int r, int val) {
                update_range(1, 1, n - 1, l, r, val);
            }

            int get_max() {
                propagate(1, 1, n - 1);
                return tree[1];
            }
        };

        vector<set<int>> pos_sets(MAXV);
        set<int> temp_primes;
        int total_distinct = 0;
        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            if (v < MAXV && is_prime[v]) {
                pos_sets[v].insert(i);
                temp_primes.insert(v);
            }
        }
        total_distinct = temp_primes.size();

        SegTree seg(n);
        for (int p : temp_primes) {
            auto& s = pos_sets[p];
            if (s.size() >= 2) {
                int L = *s.begin();
                int R = *s.rbegin();
                if (L + 1 <= R) {
                    seg.update(L + 1, R, 1);
                }
            }
        }

        vector<int> ans;
        for (auto& qu : queries) {
            int idx = qu[0];
            int val = qu[1];
            int oldv = nums[idx];

            // handle old
            if (oldv < MAXV && is_prime[oldv]) {
                int p = oldv;
                auto& s = pos_sets[p];
                int L = *s.begin();
                int R = *s.rbegin();
                if (L + 1 <= R) {
                    seg.update(L + 1, R, -1);
                }
                s.erase(idx);
                size_t sz_after = s.size();
                if (sz_after == 0) {
                    --total_distinct;
                }
                if (!s.empty()) {
                    int Ln = *s.begin();
                    int Rn = *s.rbegin();
                    if (Ln + 1 <= Rn) {
                        seg.update(Ln + 1, Rn, 1);
                    }
                }
            }

            // update array
            nums[idx] = val;

            // handle new
            if (val < MAXV && is_prime[val]) {
                int p = val;
                auto& s = pos_sets[p];
                size_t sz_before = s.size();
                if (!s.empty()) {
                    int L = *s.begin();
                    int R = *s.rbegin();
                    if (L + 1 <= R) {
                        seg.update(L + 1, R, -1);
                    }
                }
                s.insert(idx);
                if (sz_before == 0) {
                    ++total_distinct;
                }
                int Ln = *s.begin();
                int Rn = *s.rbegin();
                if (Ln + 1 <= Rn) {
                    seg.update(Ln + 1, Rn, 1);
                }
            }

            int max_strad = seg.get_max();
            ans.push_back(total_distinct + max_strad);
        }
        return ans;
    }
};
# @lc code=end