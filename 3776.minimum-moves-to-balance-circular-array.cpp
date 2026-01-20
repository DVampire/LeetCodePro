#
# @lc app=leetcode id=3776 lang=cpp
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        long long totalSum = 0;
        int negIdx = -1;
        int n = balance.size();

        for (int i = 0; i < n; ++i) {
            totalSum += balance[i];
            if (balance[i] < 0) {
                negIdx = i;
            }
        }

        if (totalSum < 0) return -1;
        if (negIdx == -1) return 0;

        long long needed = -((long long)balance[negIdx]);
        long long moves = 0;
        int l = (negIdx - 1 + n) % n;
        int r = (negIdx + 1) % n;
        long long dist = 1;

        while (needed > 0) {
            // Take from left neighbor
            long long takeL = std::min(needed, (long long)balance[l]);
            moves += takeL * dist;
            needed -= takeL;
            
            if (needed == 0) break;

            // If l and r are the same, we just processed the last unique element via l.
            // We must stop to avoid double counting.
            if (l == r) break;

            // Take from right neighbor
            long long takeR = std::min(needed, (long long)balance[r]);
            moves += takeR * dist;
            needed -= takeR;

            // Move pointers
            l = (l - 1 + n) % n;
            r = (r + 1) % n;
            dist++;
        }

        return moves;
    }
};
# @lc code=end