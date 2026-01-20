#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int dp[2][2]; // [start_char][end_char], 0 for 'A', 1 for 'B'
    Node() {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                dp[i][j] = -1e9;
    }
};

class Solution {
    int n;
    vector<Node> tree;

    Node merge(const Node& l, const Node& r) {
        Node res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                res.dp[i][j] = max(l.dp[i][j], r.dp[i][j]);
                for (int m1 = 0; m1 < 2; ++m1) {
                    for (int m2 = 0; m2 < 2; ++m2) {
                        if (m1 != m2) {
                            res.dp[i][j] = max(res.dp[i][j], l.dp[i][m1] + r.dp[m2][j]);
                        }
                    }
                }
            }
        }
        return res;
    }

    void build(const string& s, int v, int tl, int tr) {
        if (tl == tr) {
            int char_idx = s[tl] - 'A';
            tree[v].dp[char_idx][char_idx] = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(s, 2 * v, tl, tm);
            build(s, 2 * v + 1, tm + 1, tr);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            int old_a = tree[v].dp[0][0];
            tree[v].dp[0][0] = (old_a > 0) ? -1e9 : 1;
            tree[v].dp[1][1] = (old_a > 0) ? 1 : -1e9;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(2 * v, tl, tm, pos);
            else update(2 * v + 1, tm + 1, tr, pos);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    Node query(int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        if (r <= tm) return query(2 * v, tl, tm, l, r);
        if (l > tm) return query(2 * v + 1, tm + 1, tr, l, r);
        return merge(query(2 * v, tl, tm, l, tm), query(2 * v + 1, tm + 1, tr, tm + 1, r));
    }

public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        n = s.length();
        tree.assign(4 * n, Node());
        build(s, 1, 0, n - 1);
        vector<int> results;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                update(1, 0, n - 1, q[1]);
            } else {
                Node res = query(1, 0, n - 1, q[1], q[2]);
                int max_len = 0;
                for (int i = 0; i < 2; ++i)
                    for (int j = 0; j < 2; ++j)
                        max_len = max(max_len, res.dp[i][j]);
                results.push_back((q[2] - q[1] + 1) - max_len);
            }
        }
        return results;
    }
};