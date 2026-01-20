#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#
# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        long long up1 = -1e18;
        long long down = -1e18;
        long long up2 = -1e18;
        long long ans = -1e18;
        
        int n = nums.size();
        
        for (int i = 1; i < n; ++i) {
            long long curr = nums[i];
            long long prev = nums[i-1];
            
            long long next_up1 = -1e18;
            long long next_down = -1e18;
            long long next_up2 = -1e18;
            
            if (curr > prev) {
                // Update up1: extend or start new
                // Start new: prev + curr
                // Extend: up1 + curr
                long long cand = prev;
                if (up1 > -1e17) cand = max(cand, up1);
                next_up1 = cand + curr;
                
                // Update up2: extend up2 or transition from down
                // Transition: down + curr
                // Extend: up2 + curr
                if (down > -1e17 || up2 > -1e17) {
                    long long base = -1e18;
                    if (down > -1e17) base = max(base, down);
                    if (up2 > -1e17) base = max(base, up2);
                    next_up2 = base + curr;
                }
            } else if (curr < prev) {
                // Update down: extend down or transition from up1
                // Transition: up1 + curr
                // Extend: down + curr
                if (up1 > -1e17 || down > -1e17) {
                    long long base = -1e18;
                    if (up1 > -1e17) base = max(base, up1);
                    if (down > -1e17) base = max(base, down);
                    next_down = base + curr;
                }
            }
            
            up1 = next_up1;
            down = next_down;
            up2 = next_up2;
            
            if (up2 > ans) ans = up2;
        }
        
        return ans;
    }
};
# @lc code=end