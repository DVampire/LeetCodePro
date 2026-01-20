#
# @lc app=leetcode id=3464 lang=cpp
#
# [3464] Maximize the Distance Between Points on a Square
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    struct Point {
        int x, y;
        long long d;
    };

    long long get_dist(int x, int y, int side) {
        if (y == 0) return x;
        if (x == side) return (long long)side + y;
        if (y == side) return (long long)2 * side + (side - x);
        if (x == 0) return (long long)3 * side + (side - y);
        return 0;
    }

    int manhattan(const Point& a, const Point& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            pts[i].x = points[i][0];
            pts[i].y = points[i][1];
            pts[i].d = get_dist(pts[i].x, pts[i].y, side);
        }

        sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
            return a.d < b.d;
        });

        auto check = [&](int x) {
            // Doubling points to handle cycle
            vector<Point> pts2 = pts;
            for (int i = 0; i < n; ++i) pts2.push_back(pts[i]);
            
            vector<int> next(2 * n, -1);
            int right = 0;
            for (int left = 0; left < n; ++left) {
                if (right <= left) right = left + 1;
                while (right < 2 * n && manhattan(pts2[left], pts2[right]) < x) {
                    right++;
                }
                if (right < 2 * n && right < left + n) {
                    next[left] = right;
                } else {
                    next[left] = -1;
                }
            }
            
            // We only need to check starting points in the first "gap"
            // But trying all n is safe enough given the constraints.
            // Optimization: Only check the first n points as starting points.
            for (int i = 0; i < n; ++i) {
                int curr = i;
                bool possible = true;
                for (int step = 0; step < k - 1; ++step) {
                    curr = next[curr % n];
                    if (curr == -1) {
                        possible = false;
                        break;
                    }
                }
                if (possible && manhattan(pts2[curr], pts[i]) >= x) return true;
            }
            return false;
        };

        int low = 1, high = side, ans = 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
# @lc code=end