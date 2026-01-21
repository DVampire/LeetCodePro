#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (canAchieve(s, mid, numOps)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
    
    bool canAchieve(const string& s, int L, int numOps) {
        int n = s.length();
        int ops = 0;
        
        if (L == 1) {
            // Count differences from "010101..." and "101010..."
            int count0 = 0, count1 = 0;
            for (int i = 0; i < n; i++) {
                int bit = s[i] - '0';
                if (bit != (i % 2)) count0++;
                if (bit != (1 - i % 2)) count1++;
            }
            ops = min(count0, count1);
        } else {
            // For each run, count needed flips
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                int k = j - i; // run length
                ops += k / (L + 1);
                i = j;
            }
        }
        
        return ops <= numOps;
    }
};
# @lc code=end