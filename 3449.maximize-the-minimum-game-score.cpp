#
# @lc app=leetcode id=3449 lang=cpp
#
# [3449] Maximize the Minimum Game Score
#
# @lc code=start
class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        long long M = m;
        
        auto canAchieve = [&](long long target) -> bool {
            if (target <= 0) return true;
            
            long long totalMoves = n - 1;  // traversal from -1 to n-2
            long long carry = 0;
            
            for (int i = 0; i < n - 1; i++) {
                long long need = (target + points[i] - 1) / points[i];
                long long visits = (i == 0) ? 1 : carry + 1;
                long long osc = max(0LL, need - visits);
                totalMoves += 2 * osc;
                carry = osc;
                if (totalMoves > M) return false;
            }
            
            // Check position n-1
            long long need_last = (target + points[n-1] - 1) / points[n-1];
            if (carry < need_last) {
                totalMoves += 1;  // move from n-2 to n-1
                long long visits = carry + 1;
                long long osc = max(0LL, need_last - visits);
                totalMoves += 2 * osc;
            }
            
            return totalMoves <= M;
        };
        
        long long lo = 0, hi = 1LL * (*max_element(points.begin(), points.end())) * M;
        while (lo < hi) {
            long long mid = lo + (hi - lo + 1) / 2;
            if (canAchieve(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
};
# @lc code=end