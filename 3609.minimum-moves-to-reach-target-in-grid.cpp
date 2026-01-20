#include <algorithm>

class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        long long s_x = sx, s_y = sy, t_x = tx, t_y = ty;
        int moves = 0;

        while (t_x >= s_x && t_y >= s_y) {
            if (t_x == s_x && t_y == s_y) {
                return moves;
            }

            if (t_x == t_y) {
                if (t_x == 0) return -1; // Should be caught by the equality check above
                if (s_y == 0 && s_x <= t_x) {
                    t_y = 0;
                    moves++;
                } else if (s_x == 0 && s_y <= t_y) {
                    t_x = 0;
                    moves++;
                } else {
                    return -1;
                }
            } else if (t_x > t_y) {
                if (t_x < 2 * t_y) {
                    t_x -= t_y;
                    moves++;
                } else {
                    if (t_x % 2 != 0 || t_x == 0) return -1;
                    t_x /= 2;
                    moves++;
                }
            } else {
                if (t_y < 2 * t_x) {
                    t_y -= t_x;
                    moves++;
                } else {
                    if (t_y % 2 != 0 || t_y == 0) return -1;
                    t_y /= 2;
                    moves++;
                }
            }
        }

        return -1;
    }
};