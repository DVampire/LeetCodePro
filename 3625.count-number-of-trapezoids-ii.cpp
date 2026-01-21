#
# @lc app=leetcode id=3625 lang=cpp
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        set<pair<int, int>> slopes;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int g = __gcd(abs(dx), abs(dy));
                if (g != 0) {
                    dx /= g;
                    dy /= g;
                }
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }
                slopes.emplace(dy, dx);
            }
        }

        long long S = 0;
        for (const auto& sl : slopes) {
            int a = sl.first;
            int b = sl.second;
            vector<long long> cs(n);
            for (int p = 0; p < n; ++p) {
                cs[p] = (long long)b * points[p][1] - (long long)a * points[p][0];
            }
            sort(cs.begin(), cs.end());
            long long tot_seg = 0;
            long long sq_sum = 0;
            int start = 0;
            while (start < n) {
                int end = start;
                while (end < n && cs[end] == cs[start]) ++end;
                int sz = end - start;
                if (sz >= 2) {
                    long long comb = (long long)sz * (sz - 1) / 2;
                    tot_seg += comb;
                    sq_sum += comb * comb;
                }
                start = end;
            }
            long long contrib = (tot_seg * tot_seg - sq_sum) / 2;
            S += contrib;
        }

        const int OFF = 1000;
        const int SZ = 2005;
        vector<vector<char>> present(SZ, vector<char>(SZ, 0));
        for (const auto& pt : points) {
            int x = pt[0] + OFF;
            int y = pt[1] + OFF;
            present[x][y] = 1;
        }

        long long cnt = 0;
        auto valid = [&](int p1, int p2, int p3) -> bool {
            long long vx1 = points[p1][0] - points[p3][0];
            long long vy1 = points[p1][1] - points[p3][1];
            long long vx2 = points[p2][0] - points[p3][0];
            long long vy2 = points[p2][1] - points[p3][1];
            long long cross = vx1 * vy2 - vy1 * vx2;
            if (cross == 0) return false;
            int dx = points[p1][0] + points[p2][0] - points[p3][0];
            int dy = points[p1][1] + points[p2][1] - points[p3][1];
            int ox = dx + OFF;
            int oy = dy + OFF;
            if (ox < 0 || ox >= SZ || oy < 0 || oy >= SZ || !present[ox][oy]) return false;
            if (dx == points[p1][0] && dy == points[p1][1]) return false;
            if (dx == points[p2][0] && dy == points[p2][1]) return false;
            if (dx == points[p3][0] && dy == points[p3][1]) return false;
            return true;
        };

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (valid(i, j, k)) ++cnt;
                    if (valid(i, k, j)) ++cnt;
                    if (valid(j, k, i)) ++cnt;
                }
            }
        }
        long long P = cnt / 4;

        return (int)(S - P);
    }
};
# @lc code=end