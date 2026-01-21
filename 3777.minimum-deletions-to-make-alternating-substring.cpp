#
# @lc app=leetcode id=3777 lang=cpp
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
class Solution {
public:
    struct Fenwick {
        vector<int> tree;
        int n;
        Fenwick(int _n) : n(_n), tree(_n + 1, 0) {}
        void update(int idx, int val) {
            while (idx <= n) {
                tree[idx] += val;
                idx += idx & -idx;
            }
        }
        int query(int idx) {
            int sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }
        int query(int l, int r) {
            if (l > r) return 0;
            return query(r) - query(l - 1);
        }
    };

    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();
        Fenwick ft(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            int val = (s[i] != s[i + 1] ? 1 : 0);
            ft.update(i + 1, val);
        }
        vector<int> answer;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                int j = q[1];
                if (j > 0) {
                    int old_val = (s[j - 1] != s[j] ? 1 : 0);
                    int new_val = 1 - old_val;
                    int delta = new_val - old_val;
                    ft.update(j, delta);
                }
                if (j < n - 1) {
                    int old_val = (s[j] != s[j + 1] ? 1 : 0);
                    int new_val = 1 - old_val;
                    int delta = new_val - old_val;
                    ft.update(j + 1, delta);
                }
                s[j] = (s[j] == 'A' ? 'B' : 'A');
            } else {
                int l = q[1], r = q[2];
                int len = r - l + 1;
                int dels;
                if (len == 1) {
                    dels = 0;
                } else {
                    int sum_diff = ft.query(l + 1, r);
                    int runs = 1 + sum_diff;
                    dels = len - runs;
                }
                answer.push_back(dels);
            }
        }
        return answer;
    }
};
# @lc code=end