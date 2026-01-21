#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        std::map<int, std::vector<int>> x_to_ys;
        for (int i = 0; i < n; ++i) {
            x_to_ys[xCoord[i]].push_back(yCoord[i]);
        }
        for (auto& p : x_to_ys) {
            std::sort(p.second.begin(), p.second.end());
        }
        std::vector<int> xs;
        for (const auto& p : x_to_ys) {
            xs.push_back(p.first);
        }
        int m = xs.size();
        if (m < 2) return -1LL;
        std::vector<std::vector<int>> ys_by_x(m);
        for (int i = 0; i < m; ++i) {
            ys_by_x[i] = x_to_ys[xs[i]];
        }
        std::map<std::pair<int, int>, std::vector<int>> gap_to_xinds;
        for (int i = 0; i < m; ++i) {
            const auto& ys = ys_by_x[i];
            for (size_t j = 0; j + 1 < ys.size(); ++j) {
                int yb = ys[j];
                int yt = ys[j + 1];
                gap_to_xinds[{yb, yt}].push_back(i);
            }
        }
        // Merge-sort tree
        std::vector<std::vector<int>> tree(4 * m);
        std::function<void(int, int, int)> build_func = [&](int node, int l, int r) {
            if (l == r) {
                tree[node] = ys_by_x[l];
                return;
            }
            int mid = (l + r) / 2;
            build_func(2 * node, l, mid);
            build_func(2 * node + 1, mid + 1, r);
            const auto& leftv = tree[2 * node];
            const auto& rightv = tree[2 * node + 1];
            tree[node].resize(leftv.size() + rightv.size());
            std::merge(leftv.begin(), leftv.end(), rightv.begin(), rightv.end(), tree[node].begin());
        };
        if (m > 0) {
            build_func(1, 0, m - 1);
        }
        std::function<long long(int, int, int, int, int, int, int)> query_func = [&](int node, int l, int r, int ql, int qr, int ya, int yb) -> long long {
            if (ql > r || qr < l) return 0LL;
            if (ql <= l && r <= qr) {
                const auto& vec = tree[node];
                auto it1 = std::lower_bound(vec.begin(), vec.end(), ya);
                auto it2 = std::upper_bound(it1, vec.end(), yb);
                return static_cast<long long>(it2 - it1);
            }
            int mid = (l + r) / 2;
            return query_func(2 * node, l, mid, ql, qr, ya, yb) +
                   query_func(2 * node + 1, mid + 1, r, ql, qr, ya, yb);
        };
        long long ans = -1LL;
        for (const auto& gpr : gap_to_xinds) {
            const auto& xinds = gpr.second;
            size_t p = xinds.size();
            if (p < 2) continue;
            int yb_gap = gpr.first.first;
            int yt_gap = gpr.first.second;
            for (size_t r = 0; r + 1 < p; ++r) {
                int li = xinds[r];
                int ri = xinds[r + 1];
                long long width = static_cast<long long>(xs[ri]) - xs[li];
                long long height = static_cast<long long>(yt_gap) - yb_gap;
                long long area = width * height;
                int L = li + 1;
                int R = ri - 1;
                bool valid = (L > R) || (query_func(1, 0, m - 1, L, R, yb_gap, yt_gap) == 0LL);
                if (valid && area > ans) {
                    ans = area;
                }
            }
        }
        return ans;
    }
};
# @lc code=end