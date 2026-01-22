#
# @lc app=leetcode id=3609 lang=cpp
#
# [3609] Minimum Moves to Reach Target in Grid
#
# @lc code=start
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return 0;
        if (tx < sx || ty < sy) return -1;
        if (sx == 0 && sy == 0) return -1;  // Can't move from (0, 0)
        
        long long steps = 0;
        long long lsx = sx, lsy = sy, ltx = tx, lty = ty;
        
        while (ltx != lsx || lty != lsy) {
            if (ltx < lsx || lty < lsy) return -1;
            
            if (ltx == lty) {
                // Can only go to (0, lty) or (ltx, 0)
                if (lsx == 0) {
                    ltx = 0;
                    steps++;
                } else if (lsy == 0) {
                    lty = 0;
                    steps++;
                } else {
                    return -1;
                }
            } else if (ltx > lty) {
                if (lty == 0) {
                    // Can only halve ltx
                    if (lsy != 0) return -1;
                    if (ltx == lsx) break;
                    if (ltx % 2 != 0) return -1;
                    ltx /= 2;
                    steps++;
                } else if (ltx >= 2 * lty) {
                    // Halve ltx
                    if (ltx % 2 != 0) return -1;
                    ltx /= 2;
                    steps++;
                } else {
                    // Subtract: lty <= ltx < 2*lty
                    ltx -= lty;
                    steps++;
                }
            } else {  // lty > ltx
                if (ltx == 0) {
                    // Can only halve lty
                    if (lsx != 0) return -1;
                    if (lty == lsy) break;
                    if (lty % 2 != 0) return -1;
                    lty /= 2;
                    steps++;
                } else if (lty >= 2 * ltx) {
                    // Halve lty
                    if (lty % 2 != 0) return -1;
                    lty /= 2;
                    steps++;
                } else {
                    // Subtract: ltx <= lty < 2*ltx
                    lty -= ltx;
                    steps++;
                }
            }
        }
        
        return (int)steps;
    }
};
# @lc code=end