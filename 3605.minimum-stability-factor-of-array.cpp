//
// @lc app=leetcode id=3605 lang=cpp
//
// [3605] Minimum Stability Factor of Array
//

// @lc code=start
class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        
        // Build sparse table for GCD
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        vector<vector<int>> sparse(LOG, vector<int>(n));
        
        for (int i = 0; i < n; i++) {
            sparse[0][i] = nums[i];
        }
        
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                sparse[j][i] = __gcd(sparse[j-1][i], sparse[j-1][i + (1 << (j-1))]);
            }
        }
        
        auto queryGCD = [&](int l, int r) -> int {
            int len = r - l + 1;
            int k = 31 - __builtin_clz(len);
            return __gcd(sparse[k][l], sparse[k][r - (1 << k) + 1]);
        };
        
        auto canAchieve = [&](int k) -> bool {
            int breakers = 0;
            int lastBreaker = -1;
            for (int i = 0; i + k < n; i++) {
                if (lastBreaker < i) {
                    if (queryGCD(i, i + k) >= 2) {
                        lastBreaker = i + k;
                        breakers++;
                    }
                }
            }
            return breakers <= maxC;
        };
        
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (canAchieve(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }
};
// @lc code=end