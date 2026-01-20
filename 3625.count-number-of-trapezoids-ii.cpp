#
# @lc app=leetcode id=3625 lang=cpp
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
#include <vector>
#include <map>
#include <numeric>

using namespace std;

class Solution {
public:
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    pair<int, int> get_slope(int dx, int dy) {
        if (dx == 0) return {0, 1};
        if (dy == 0) return {1, 0};
        int g = gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
        if (dx < 0) {
            dx = -dx;
            dy = -dy;
        } else if (dx == 0 && dy < 0) {
            dy = -dy;
        }
        return {dx, dy};
    }

    long long countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        // slope_line_counts[slope][intercept] = number of pairs on that specific line
        map<pair<int, int>, map<long long, int>> slope_line_counts;
        // midpoint_slope_counts[midpoint][slope] = number of pairs with that midpoint and slope
        map<pair<int, int>, map<pair<int, int>, int>> midpoint_slope_counts;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                pair<int, int> slope = get_slope(dx, dy);

                // Line equation: a*x + b*y = c
                // Normal vector (a, b) is (-dy, dx)
                long long a = -dy;
                long long b = dx;
                long long c = a * points[i][0] + b * points[i][1];
                slope_line_counts[slope][c]++;

                pair<int, int> midpoint = {points[i][0] + points[j][0], points[i][1] + points[j][1]};
                midpoint_slope_counts[midpoint][slope]++;
            }
        }

        long long total_trapezoid_counts = 0;
        for (auto const& [slope, line_map] : slope_line_counts) {
            long long sum_X = 0;
            long long sum_X_sq = 0;
            for (auto const& [intercept, count] : line_map) {
                sum_X += count;
                sum_X_sq += (long long)count * count;
            }
            total_trapezoid_counts += (sum_X * sum_X - sum_X_sq) / 2;
        }

        long long parallelogram_counts = 0;
        for (auto const& [midpoint, slope_map] : midpoint_slope_counts) {
            long long sum_S = 0;
            long long sum_S_sq = 0;
            for (auto const& [slope, count] : slope_map) {
                sum_S += count;
                sum_S_sq += (long long)count * count;
            }
            parallelogram_counts += (sum_S * sum_S - sum_S_sq) / 2;
        }

        return total_trapezoid_counts - parallelogram_counts;
    }
};
# @lc code=end