#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Special case: check if we can achieve length 1 (alternating pattern)
        int mismatch1 = 0, mismatch2 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] - '0' != i % 2) mismatch1++;
            if (s[i] - '0' != 1 - i % 2) mismatch2++;
        }
        if (min(mismatch1, mismatch2) <= numOps) {
            return 1;
        }
        
        // Binary search on the answer
        int left = 2, right = n;
        int ans = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, mid, numOps)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }
    
    bool canAchieve(string& s, int k, int numOps) {
        int n = s.length();
        int flips = 0;
        int i = 0;
        
        while (i < n) {
            int j = i;
            // Find the end of current consecutive substring
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            
            // Calculate flips needed to break this substring
            if (len > k) {
                flips += len / (k + 1);
            }
            
            if (flips > numOps) {
                return false;
            }
            
            i = j;
        }
        
        return true;
    }
};
# @lc code=end