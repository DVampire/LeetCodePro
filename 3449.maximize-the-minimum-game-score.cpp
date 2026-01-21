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
        
        auto canAchieve = [&](long long target) -> bool {
            vector<long long> visits(n);
            long long maxVisits = 0;
            for (int i = 0; i < n; i++) {
                visits[i] = (target + points[i] - 1) / points[i];
                maxVisits = max(maxVisits, visits[i]);
            }
            
            if (maxVisits > m) return false;
            
            long long totalCost = 0;
            for (long long k = 1; k <= maxVisits; k++) {
                int left = -1, right = -1;
                for (int i = 0; i < n; i++) {
                    if (visits[i] >= k) {
                        if (left == -1) left = i;
                        right = i;
                    }
                }
                
                if (k == 1) {
                    totalCost += right + 1;
                } else {
                    int prevRight = -1;
                    for (int i = 0; i < n; i++) {
                        if (visits[i] >= k - 1) {
                            prevRight = i;
                        }
                    }
                    totalCost += prevRight + right - 2LL * left;
                }
                
                if (totalCost > m) return false;
            }
            
            return true;
        };
        
        long long left = 0, right = (long long)1e15;
        long long answer = 0;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (canAchieve(mid)) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return answer;
    }
};
# @lc code=end