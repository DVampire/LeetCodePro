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
        
        // Find maximum consecutive run length
        int maxRun = 0;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            maxRun = max(maxRun, j - i);
            i = j;
        }
        
        // Special case: check if we can achieve alternating pattern (length 1)
        int flips1 = 0, flips2 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != ('0' + i % 2)) flips1++;
            if (s[i] != ('1' - i % 2)) flips2++;
        }
        if (min(flips1, flips2) <= numOps) {
            return 1;
        }
        
        // Binary search on the answer [2, maxRun]
        int left = 2, right = maxRun;
        int result = maxRun;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, mid, numOps)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
    bool canAchieve(const string& s, int k, int numOps) {
        int n = s.length();
        int flips = 0;
        int i = 0;
        
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            if (len > k) {
                flips += len / (k + 1);
            }
            i = j;
        }
        
        return flips <= numOps;
    }
};
# @lc code=end