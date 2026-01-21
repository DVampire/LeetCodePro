#
# @lc app=leetcode id=3609 lang=cpp
#
# [3609] Minimum Moves to Reach Target in Grid
#
# @lc code=start
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        long long moves = 0;
        long long tx_ll = tx, ty_ll = ty, sx_ll = sx, sy_ll = sy;
        
        while (tx_ll != sx_ll || ty_ll != sy_ll) {
            if (tx_ll < sx_ll || ty_ll < sy_ll) {
                return -1;
            }
            if (tx_ll == ty_ll) {
                if ((sx_ll == 0 && sy_ll == ty_ll) || (sx_ll == tx_ll && sy_ll == 0)) {
                    return moves + 1;
                }
                return -1;
            }
            if (tx_ll > ty_ll) {
                if (ty_ll > sy_ll) {
                    if (tx_ll <= 2 * ty_ll) {
                        long long k = std::min((tx_ll - ty_ll - 1) / ty_ll, (tx_ll - sx_ll) / ty_ll);
                        if (k < 1) k = 1;
                        tx_ll -= k * ty_ll;
                        moves += k;
                    } else {
                        if (tx_ll % 2 == 0) {
                            tx_ll /= 2;
                            moves++;
                        } else {
                            return -1;
                        }
                    }
                } else if (ty_ll == sy_ll) {
                    long long cur_x = tx_ll;
                    long long steps = 0;
                    while (cur_x > sx_ll) {
                        if (cur_x <= 2 * sy_ll) {
                            long long k = std::min((cur_x - sy_ll - 1) / sy_ll, (cur_x - sx_ll) / sy_ll);
                            if (k < 1) k = 1;
                            cur_x -= k * sy_ll;
                            steps += k;
                        } else {
                            if (cur_x % 2 == 0) {
                                cur_x /= 2;
                                steps++;
                            } else {
                                return -1;
                            }
                        }
                    }
                    if (cur_x == sx_ll) {
                        return moves + steps;
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            } else {
                if (tx_ll > sx_ll) {
                    if (ty_ll <= 2 * tx_ll) {
                        long long k = std::min((ty_ll - tx_ll - 1) / tx_ll, (ty_ll - sy_ll) / tx_ll);
                        if (k < 1) k = 1;
                        ty_ll -= k * tx_ll;
                        moves += k;
                    } else {
                        if (ty_ll % 2 == 0) {
                            ty_ll /= 2;
                            moves++;
                        } else {
                            return -1;
                        }
                    }
                } else if (tx_ll == sx_ll) {
                    long long cur_y = ty_ll;
                    long long steps = 0;
                    while (cur_y > sy_ll) {
                        if (cur_y <= 2 * tx_ll) {
                            long long k = std::min((cur_y - tx_ll - 1) / tx_ll, (cur_y - sy_ll) / tx_ll);
                            if (k < 1) k = 1;
                            cur_y -= k * tx_ll;
                            steps += k;
                        } else {
                            if (cur_y % 2 == 0) {
                                cur_y /= 2;
                                steps++;
                            } else {
                                return -1;
                            }
                        }
                    }
                    if (cur_y == sy_ll) {
                        return moves + steps;
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            }
        }
        return moves;
    }
};
# @lc code=end